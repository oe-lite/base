DESCRIPTION = "ISC Internet Domain Name Server"
HOMEPAGE = "http://www.isc.org/sw/bind/"
LICENSE = "ISC"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools sysvinit

DEPENDS = "libssl libcrypto ${DEPENDS_LIBC}"
DEPENDS_LIBC = "libdl"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
RDEPENDS_${PN} = "${PN}-config"

SRC_URI = "ftp://ftp.isc.org/isc/bind9/${PV}/${PN}-${PV}.tar.gz"

# --enable-exportlib is necessary for building dhcp
EXTRA_OECONF = "\
    --enable-ipv6=no \
    --with-randomdev=/dev/random \
    --disable-threads \
    --disable-devpoll --disable-epoll \
    --sysconfdir=${sysconfdir}/bind \
    --with-openssl=${TARGET_SYSROOT}${target_prefix} \
    --with-gssapi=no \
    --with-libxml2=${TARGET_SYSROOT}${target_prefix} \
    --enable-exportlib \
    --with-export-includedir=${includedir} \
    --with-export-libdir=${libdir} \
"

RECIPE_FLAGS += "bind_zlib"
EXTRA_OECONF_ZLIB = "--without-zlib"
EXTRA_OECONF_ZLIB:USE_bind_zlib = "--with-zlib"
EXTRA_OECONF += "${EXTRA_OECONF_ZLIB}"
DEPENDS:>USE_bind_zlib = " libz"
DEPENDS_${PN}:>USE_bind_zlib = " libz"
RDEPENDS_${PN}:>USE_bind_zlib = " libz"
DEPENDS_${PN}-utils:>USE_bind_zlib = " libz"
RDEPENDS_${PN}-utils:>USE_bind_zlib = " libz"

RECIPE_FLAGS += "bind_sysvinit_start bind_sysvinit_stop"
SYSVINI_SCRIPT_bind = "bind"
DEFAULT_USE_bind_sysvinit_start= "20"
DEFAULT_USE_bind_sysvinit_stop = "20"

RECIPE_FLAGS += "bind_openssl"
DEFAULT_USE_bind_openssl = True
EXTRA_OECONF += "${EXTRA_OECONF_OPENSSL}"
EXTRA_OECONF_OPENSSL = " --without-openssl"
EXTRA_OECONF_OPENSSL:USE_bind_openssl = ""

# last verified with bind-9.7.2-P3
PARALLEL_MAKE = ""

do_install[postfuncs] =+ "do_install_extra_files"
do_install_extra_files() {
	rm "${D}/usr/bin/nslookup"
	install -d "${D}/etc/bind"
	install -d "${D}/etc/init.d"
	install -m 644 ${S}/conf/* "${D}/etc/bind"
	install -m 755 "${S}/init.d" "${D}/etc/init.d/bind"
}

inherit binconfig
BINCONFIG_FILES = "${bindir}/isc-config.sh"
FILES_${PN}-dev += "${bindir}/isc-config.sh"
DEPENDS_${PN}-dev = "libssl libcrypto ${DEPENDS_LIBC}"

# The named configuration file includes named.conf.local,
# hence to make machine/project specific configuration provide
# a named.conf.local and override the "-config" package
FILES_${PN}-config = "${sysconfdir}/bind/named.conf.local"
PACKAGES =+ "${PN}-utils ${PN}-config"
FILES_${PN}-utils = "${bindir}/host ${bindir}/dig ${bindir}/nslookup"
