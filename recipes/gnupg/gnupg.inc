DESCRIPTION = "gnupg - GNU privacy guard"
HOMEPAGE = "http://www.gnupg.org/"
LICENSE = "GPLv2"

inherit autotools gettext

DEPENDS = "zlib bzip2"

MIRRORS ="""
ftp://ftp.gnupg.org/gcrypt
http://mirrors.rootmode.com/ftp.gnupg.org
"""

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/gnupg/gnupg-${PV}.tar.bz2"

S = "${SRCDIR}/gnupg-${PV}"

EXTRA_OECONF = "--disable-ldap \
		--with-zlib \
		--with-bzip2 \
		--disable-selinux-support"

do_install[postfuncs] =+ "do_install_post"

do_install_post() {
	install -d ${D}${docdir}/${PN}
	mv ${D}${datadir}/${PN}/* ${D}/${docdir}/${PN}/ || :
	mv ${D}${prefix}/doc/* ${D}/${docdir}/${PN}/ || :
}

# split out gpgv from main package
RDEPENDS_gnupg = "gpgv"
PACKAGES =+ "gpgv"
FILES_gpgv = "${bindir}/gpgv"

# Exclude debug files from the main packages
FILES_${PN} = "${bindir}/* ${datadir}/${PN} ${libexecdir}/${PN}/*"
FILES_${PN}-dbg += "${libexecdir}/${PN}/.debug"
