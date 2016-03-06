DESCRIPTION = "A small library that defines common values for all GnuPG components"
HOMEPAGE = "http://www.gnupg.org/related_software/libgpg-error/"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "native machine sdk"

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/libgpg-error/libgpg-error-${PV}.tar.bz2"

inherit autotools binconfig pkgconfig gettext library

DEPENDS += "libpthread"

do_compile[prefuncs] += "do_compile_prepend"
do_compile_prepend() {
	TARGET_FILE=linux-gnu
	if [ ${TARGET_OS} != "linux" ]; then
		TARGET_FILE=${TARGET_OS}
	fi

	case ${TARGET_ARCH} in
	  arm-*)	      TUPLE=arm-unknown-linux-gnueabi ;;
	  aarch64-*)	      TUPLE=aarch64-unknown-linux-gnu ;;
	  i586-*|i686-*)  TUPLE=i686-pc-linux-gnu ;;
	  x86_64-*)     TUPLE=x86_64-pc-linux-gnu ;;
	  powerpc-*)	TUPLE=powerpc-unknown-linux-gnu ;;
	  *)          TUPLE=${TARGET_ARCH}-unknown-linux-gnu ;;
	esac

	cp ${SRCDIR}/${PN}-${PV}/src/syscfg/lock-obj-pub.$TUPLE.h \
	  ${SRCDIR}/${PN}-${PV}/src/syscfg/lock-obj-pub.$TARGET_FILE.h
}

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
