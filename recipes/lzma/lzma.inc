DESCRIPTION = "LZMA is a general compression method. LZMA provides high \
	compression ratio and very fast decompression."
HOMEPAGE = "http://www.7-zip.org/"
LICENSE = "LGPL"

RECIPE_TYPES = "machine native sdk"

inherit c c++ make

SRC_URI = "http://downloads.sourceforge.net/sevenzip/lzma${@bb.data.getVar('PV',d,1).replace('.','')}.tar.bz2"
S = "${SRCDIR}"

DEPENDS = "libz"

EXTRA_OEMAKE = "-f makefile.gcc"

CFLAGS += "-c -I${S}"
