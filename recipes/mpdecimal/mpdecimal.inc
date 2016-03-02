DESCRIPTION = "Package for correctly-rounded arbitrary precision decimal floating point arithmetic"
LICENSE = "BSD-2-Clause"
HOMEPAGE = "http://www.bytereef.org/mpdecimal/index.html"
RECIPE_TYPES = "machine native sdk"

inherit autotools library

DEPENDS = "libm"
SRC_URI = "http://www.bytereef.org/software/${PN}/releases/${PN}-${PV}.tar.gz"
SRC_URI:>HOST_LIBC_mingw = " file://fix-mingw-lib-names.patch"

LIBRARY_NAME = "libmpdec"
LIBRARY_VERSION = "2"

# fix FILES for mingw builds
FILES_${PN}:>HOST_LIBC_mingw = " \
    ${libdir}/${LIBRARY_NAME}-${PV}.dll \
    ${libdir}/${LIBRARY_NAME}-${LIBRARY_VERSION}.dll \
"
FILES_${PN}-dev:>HOST_LIBC_mingw = " \
    ${libdir}/${LIBRARY_NAME}.dll \
    ${libdir}/${LIBRARY_NAME}-${PV}.dll.a \
"

DEPENDS_${PN} += "libc libm"
RDEPENDS_${PN} += "libc libm"

# package passes incompatible CFLAGS to linker, so use gcc to link
export LD="${CCLD}"
