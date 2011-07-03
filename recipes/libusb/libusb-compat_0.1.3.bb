DESCRIPTION = "libusb-0 compatibility library using libusb-1"
HOMEPAGE = "http://libusb.sf.net"
LICENSE = "LGPLv2.1"

inherit autotools library pkgconfig

DEPENDS = "libusb1 libpthread"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/${P}.tar.bz2"

EXTRA_OECONF = "--disable-build-docs"

PROVIDES_${PN}		= "libusb0"
PROVIDES_${PN}-dev	= "libusb0-dev"

DEPENDS_${PN} += "libusb1 libpthread"
