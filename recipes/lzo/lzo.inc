DESCRIPTION = "Lossless data compression library"
HOMEPAGE = "http://www.oberhumer.com/opensource/lzo/"

RECIPE_TYPES = "machine native sdk"

inherit autotools library

SRC_URI = "http://www.oberhumer.com/opensource/lzo/download/lzo-${PV}.tar.gz"

EXTRA_OECONF = "--enable-shared"

LIBRARY_NAME = "liblzo2"

# OE-lite/base 3 compatibility
PROVIDES_${PN} = "liblzo"
PROVIDES_${PN}[qa] += "allow-missing-soname:liblzo"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
