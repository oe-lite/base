# -*- mode:python; -*-
DESCRIPTION = "Lightweight high-performance web server"
HOMEPAGE = "http://www.lighttpd.net/"
BUGTRACKER = "http://redmine.lighttpd.net/projects/lighttpd/issues"

COMPATIBLE_HOST_ARCHS = ".*linux"

RECIPE_TYPES = "machine sdk"

inherit autotools pkgconfig gettext sysvinit make passwd

DEPENDS = "libdl libm"

SRC_URI =  "http://download.lighttpd.net/lighttpd/releases-1.4.x/lighttpd-${PV}.tar.xz"
SRC_URI += "file://lighttpd.conf"
SRC_URI += "file://index.html"
SRC_URI += "file://lighttpd"
SRC_URI += "file://passwd file://group"

EXTRA_OECONF = " \
	--without-libev \
	--without-mysql \
	--without-ldap \
	--without-attr \
	--without-valgrind \
	--without-kerberos5 \
	--without-fam \
	--without-webdav-props \
	--without-webdav-locks \
	--without-gdbm \
	--without-memcache \
"

RECIPE_FLAGS += "lighttpd_lfs"
EXTRA_OECONF_LFS = "--disable-lfs"
EXTRA_OECONF_LFS:USE_lighttpd_lfs = "--enable-lfs"
EXTRA_OECONF += "${EXTRA_OECONF_LFS}"

RECIPE_FLAGS += "lighttpd_ipv6"
EXTRA_OECONF_IPV6 = "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_lighttpd_ipv6 = "--enable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"

RECIPE_FLAGS += "lighttpd_pcre"
DEFAULT_USE_lighttpd_pcre = "1"
EXTRA_OECONF_PCRE = "--without-pcre"
EXTRA_OECONF_PCRE:USE_lighttpd_pcre = "--with-pcre"
EXTRA_OECONF += "${EXTRA_OECONF_PCRE}"
DEPENDS_PCRE = ""
DEPENDS_PCRE:USE_lighttpd_pcre = "libpcre"
DEPENDS += "${DEPENDS_PCRE}"
DEPENDS_${PN} += "libc libcrypto libdl libm libpcre libssl libz"
RDEPENDS_${PN} += "${DEPENDS_PCRE}"

RECIPE_FLAGS += "lighttpd_zlib"
DEFAULT_USE_lighttpd_zlib = "1"
EXTRA_OECONF_ZLIB = "--without-zlib"
EXTRA_OECONF_ZLIB:USE_lighttpd_zlib = "--with-zlib"
EXTRA_OECONF += "${EXTRA_OECONF_ZLIB}"
DEPENDS_ZLIB = ""
DEPENDS_ZLIB:USE_lighttpd_zlib = "libz"
DEPENDS += "${DEPENDS_ZLIB}"
RDEPENDS_${PN} += "${DEPENDS_ZLIB}"

RECIPE_FLAGS += "lighttpd_bzip2"
EXTRA_OECONF_BZIP2 = "--without-bzip2"
EXTRA_OECONF_BZIP2:USE_lighttpd_bzip2 = "--with-bzip2"
EXTRA_OECONF += "${EXTRA_OECONF_BZIP2}"
DEPENDS_BZIP2 = ""
DEPENDS_BZIP2:USE_lighttpd_bzip2 = "libbz2"
DEPENDS += "${DEPENDS_BZIP2}"
RDEPENDS_${PN} += "${DEPENDS_BZIP2}"

RECIPE_FLAGS += "lighttpd_ssl"
DEFAULT_USE_lighttpd_ssl = "1"
EXTRA_OECONF_SSL = "--without-openssl"
EXTRA_OECONF_SSL:USE_lighttpd_ssl = "--with-openssl=${STAGE_DIR}/${HOST_TYPE}${prefix}"
EXTRA_OECONF += "${EXTRA_OECONF_SSL}"
DEPENDS_SSL = ""
DEPENDS_SSL:USE_lighttpd_ssl = "libssl libcrypto"
DEPENDS += "${DEPENDS_SSL}"
RDEPENDS_${PN} += "${DEPENDS_SSL}"

RECIPE_FLAGS += "lighttpd_sysvinit_start"
DEFAULT_USE_lighttpd_sysvinit_start = "70"
DEFAULT_USE_lighttpd_sysvinit_stop = "0"
SYSVINIT_SCRIPT_lighttpd = "lighttpd"
do_install[postfuncs] =+ "${do_install_lighttpd_sysvinit_ENABLED}"
do_install_lighttpd_sysvinit_ENABLED = ""
do_install_lighttpd_sysvinit_ENABLED:USE_sysvinit = "do_install_lighttpd_sysvinit"
do_install_lighttpd_sysvinit() {
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${SRCDIR}/lighttpd ${D}${sysconfdir}/init.d/
}

inherit s6rc
S6RC_LONGRUN_SERVICES = "lighttpd"
SRC_URI:>USE_s6rc = " file://lighttpd.run"
RECIPE_FLAGS += "lighttpd_s6rc_dependencies"

do_install[postfuncs] =+ "do_install_lighttpd_extra"
do_install_lighttpd_extra() {
    install -d ${D}${sysconfdir} ${D}/www/logs ${D}/www/pages/dav ${D}/www/var
    install -m 0755 ${SRCDIR}/lighttpd.conf ${D}${sysconfdir}/
    install -m 0644 ${SRCDIR}/index.html ${D}/www/pages/
}

PACKAGES =+ "${PN}-config"
FILES_${PN} += "${sysconfdir}"
FILES_${PN} += "${libdir}/mod_*"
FILES_${PN} += "/www"
FILES_${PN}-config = "${sysconfdir}/lighttpd.conf"
FILES_${PN}-config += "/www/pages/"
RDEPENDS_${PN} += "${PN}-config"

RDEPENDS_${PN} += "libc libgcc libdl libm"
