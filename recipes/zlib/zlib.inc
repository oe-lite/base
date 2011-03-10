DESCRIPTION = "Zlib Compression Library"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

inherit autotools library

BBCLASSEXTEND = "native"

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

oe_runconf() {
	./configure \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--includedir=${includedir}
}

PROVIDES_${PN}-dev	+= "libz${RE}"
RPROVIDES_${PN}		+= "libz${RE}"
RPROVIDES_${PN}-dev	+= "libz${RE}-dev"
