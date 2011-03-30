DESCRIPTION = "Lossless data compression library"
HOMEPAGE = "http://www.oberhumer.com/opensource/lzo/"
LICENSE = "GPLv2"

inherit autotools library

BBCLASSEXTEND = "native"

SRC_URI = "http://www.oberhumer.com/opensource/lzo/download/lzo-${PV}.tar.gz"

EXTRA_OECONF = "--enable-shared"

PROVIDES_${PN}-dev	+= "liblzo${RE}"
RPROVIDES_${PN}		+= "liblzo${RE}"
