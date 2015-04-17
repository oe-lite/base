DESCRIPTION = "A small library that defines common values for all GnuPG components"
HOMEPAGE = "http://www.gnupg.org/related_software/libgpg-error/"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/libgpg-error/libgpg-error-${PV}.tar.bz2"

inherit autotools-autoreconf binconfig pkgconfig gettext library

do_install[postfuncs] += "do_install_append"
do_install_append() {
	# we don't have common lisp in OE
	rm -rf "${D}${datadir}/common-lisp/"
}

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "gpg-error"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
DEPENDS_${PN}-gpg-error += "libc libgpg-error"
RDEPENDS_${PN}-gpg-error += "libc libgpg-error"
