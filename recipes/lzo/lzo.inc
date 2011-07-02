DESCRIPTION = "Lossless data compression library"
HOMEPAGE = "http://www.oberhumer.com/opensource/lzo/"
LICENSE = "GPLv2"

RECIPE_TYPES = "machine native sdk"

inherit autotools library

SRC_URI = "http://www.oberhumer.com/opensource/lzo/download/lzo-${PV}.tar.gz"

EXTRA_OECONF = "--enable-shared"

PROVIDES_${PN} += "liblzo"
PROVIDES_${PN} += "liblzo-dev"
