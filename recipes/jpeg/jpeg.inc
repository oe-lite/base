DESCRIPTION = "libjpeg is a library for handling the JPEG (JFIF) image format."
LICENSE = "jpeg"

inherit autotools library

RECIPE_TYPES = "machine native"

SRC_URI = "http://www.ijg.org/files/jpegsrc.v${PV}.tar.gz"

EXTRA_OECONF = "--enable-static --enable-shared"
CFLAGS_append = " -D_REENTRANT"

PACKAGES =+ "${PN}-tools "
FILES_${PN}-tools = "${bindir}/*"

PROVIDES_${PN}     = "libjpeg"
PROVIDES_${PN}-dev = "libjpeg-dev"
