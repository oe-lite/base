DESCRIPTION = "Zlib Compression Library"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

inherit autotools library

RECIPE_TYPES = "machine native sdk"

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

autotools_configure() {
	./configure \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--includedir=${includedir}
}

PROVIDES_${PN} += "libz"
