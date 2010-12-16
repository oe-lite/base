DESCRIPTION = "Zlib Compression Library"
SECTION = "libs"
PRIORITY = "required"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

inherit autotools

BBCLASSEXTEND = "native"

oe_runconf() {
	./configure \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--includedir=${includedir}
}

PARALLEL_MAKE = ""
