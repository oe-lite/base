DESCRIPTION = "Zlib Compression Library"
SECTION = "libs"
PRIORITY = "required"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

inherit autotools library
BBCLASSEXTEND = "native"

PROVIDES_${PN}-dev	+= "libz${RE}"
RPROVIDES_${PN}		+= "libz${RE}"

oe_runconf() {
	./configure \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--includedir=${includedir}
}

PARALLEL_MAKE = ""
