DESCRIPTION = "libusb-0 compatibility library using libusb-1"
HOMEPAGE = "http://libusb.sf.net"
SECTION = "libs"
LICENSE = "LGPLv2.1"

PROVIDES_${PN}	= "libusb0"
RPROVIDES_${PN}	= "libusb0"

DEPENDS		= "libusb1"
DEPENDS_${PN}	= "libusb1"
RDEPENDS_${PN}	= "libusb1"

SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/${P}.tar.bz2"

inherit autotools
# FIXME: inherit autotools binconfig lib_package

EXTRA_OECONF = "--disable-build-docs"
