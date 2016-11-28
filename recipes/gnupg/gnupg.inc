DESCRIPTION = "gnupg - GNU privacy guard"
HOMEPAGE = "http://www.gnupg.org/"
LICENSE = "GPL-3.0+, LGPL-3.0+"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools gettext
RECIPE_TYPES = "native machine sdk"

DEPENDS = "zlib bzip2 libgpg-error-config"

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

# Exclude debug files from the main packages
FILES_${PN} = "${bindir}/* ${datadir}/${PN} ${libexecdir}/${PN}/*"
FILES_${PN}-dbg += "${libexecdir}/${PN}/.debug"
