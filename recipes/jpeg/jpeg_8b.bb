DESCRIPTION = "libjpeg is a library for handling the JPEG (JFIF) image format."
LICENSE = "jpeg"

inherit autotools

BBCLASSEXTEND = "native"

SRC_URI = "\
    http://www.ijg.org/files/jpegsrc.v${PV}.tar.gz \
    "
S = "${SRCDIR}/jpeg-${PV}"

EXTRA_OECONF = "--enable-static --enable-shared"
CFLAGS_append = " -D_REENTRANT"

PACKAGES =+ "${PN}-tools "
FILES_${PN}-tools = "${bindir}/*"

