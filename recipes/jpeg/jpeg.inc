DESCRIPTION = "libjpeg is a library for handling the JPEG (JFIF) image format."
LICENSE = "jpeg"

inherit autotools library

RECIPE_TYPES = "machine native"

SRC_URI = "http://www.ijg.org/files/jpegsrc.v${PV}.tar.gz"

EXTRA_OECONF = "--enable-static --enable-shared"
CFLAGS += "-D_REENTRANT"

PACKAGES =+ "${PN}-tools "

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
DEPENDS_${PN}-tools += "libjpeg libc"
RDEPENDS_${PN}-tools += "libjpeg libc"

FILES_${PN}-tools = "${bindir}/*"
