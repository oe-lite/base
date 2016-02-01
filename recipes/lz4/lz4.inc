SUMMARY = "Extremely Fast Compression algorithm"
DESCRIPTION = "LZ4 is lossless compression algorithm, providing compression speed at 400 MB/s per core (0.16 Bytes/cycle). It features an extremely fast decoder, with speed in multiple GB/s per core (0.71 Bytes/cycle). A high compression derivative, called LZ4_HC, is available, trading customizable CPU time for compression ratio."
LICENSE = "BSD"

RECIPE_TYPES = "native machine"

SRC_URI = "https://github.com/Cyan4973/lz4/archive/${PV}.tar.gz"
S = "${SRCDIR}/lz4-${PV}"

inherit c make

EXTRA_OEMAKE = "PREFIX=${prefix} LIBDIR=${libdir} INCLUDEDIR=${includedir}"
EXTRA_OEMAKE:>HOST_LIBC_mingw = " OS=Windows"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "lz4"
LIBRARY_VERSION = "1"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc"
AUTO_PACKAGE_LIBS_DEPENDS = "libc"
FILES_${PN}-liblz4-dev += "${includedir} ${libdir}/pkgconfig"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "lz4 lz4c lz4cat unlz4"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc"
AUTO_PACKAGE_UTILS_DEPENDS = "libc"
