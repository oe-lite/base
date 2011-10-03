DESCRIPTION = "Zlib Compression Library"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

RECIPE_TYPES = "machine native sdk"

inherit autotools library

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

autotools_configure() {
	./configure \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--includedir=${includedir}
}

LIBRARY_NAME = "libz"
