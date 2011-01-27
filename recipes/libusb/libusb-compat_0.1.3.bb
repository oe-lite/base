DESCRIPTION = "libusb-0 compatibility library using libusb-1"
HOMEPAGE = "http://libusb.sf.net"
LICENSE = "LGPLv2.1"

inherit autotools library
# FIXME: inherit autotools binconfig lib_package

DEPENDS		= "libusb1-dev ${TARGET_ARCH}/sysroot-libpthread"
DEPENDS_${PN}	+= "libusb1-dev ${TARGET_ARCH}/sysroot-libpthread"
RDEPENDS_${PN}	= "libusb1"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/${P}.tar.bz2"

PROVIDES_${PN}	+= "libusb0"
RPROVIDES_${PN}	= "libusb0"

EXTRA_OECONF = "--disable-build-docs"
