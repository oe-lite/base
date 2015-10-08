# -*- mode:python; -*-
DESCRIPTION = "GNU libiconv - libiconv is for you if your application needs to \
	support multiple character encodings, but that support lacks from your \
	system."
HOMEPAGE = "http://www.gnu.org/software/libiconv"

RECIPE_TYPES = "machine native sdk"

SRC_URI = "ftp://ftp.gnu.org/pub/gnu/libiconv/libiconv-${PV}.tar.gz"

inherit library autotools

EXTRA_OECONF += "--enable-shared --enable-static --disable-rpath"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "charset"
FILES_${PN}-libcharset += "${libdir}/charset.alias"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"

PACKAGES += "${PN}-preload"
FILES_${PN}-preload = "${sharedlibdir}/preloadable_libiconv${SOLIBSDEV}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "iconv"
PROVIDES_${PN}-iconv = "${PN}-tools"

FILE_PRIORITY_${PN}-dev = "0 ${includedir}/iconv.h:1"

LIBRARY_VERSION = "2"
DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"

LIBRARY_VERSION_${PN}-libcharset = "1"
DEPENDS_${PN}-libcharset = "libc"
RDEPENDS_${PN}-libcharset = "libc"

DEPENDS_${PN}-iconv = "libc libiconv"
RDEPENDS_${PN}-iconv = "libc libiconv"

PROVIDES_${PN}-preload = "libiconv-preload"
PROVIDES_${PN}-preload[qa] = "allow-missing-provides"
DEPENDS_${PN}-preload = "libc"
RDEPENDS_${PN}-preload = "libc"
