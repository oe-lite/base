DESCRIPTION = "Jansson is a C library for encoding, decoding and manipulating \
JSON data"
HOMEPAGE = "www.digip.org/jansson/"
LICENSE = "MIT"
RECIPE_TYPES = "machine native"

SRC_URI = "http://www.digip.org/jansson/releases/jansson-${PV}.tar.bz2"

inherit autotools
AUTOTOOLS_DISTCLEAN = "0"

inherit library

DEPENDS_${PN} += "libc"
