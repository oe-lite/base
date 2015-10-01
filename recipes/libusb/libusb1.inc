DESCRIPTION = "library to provide userspace access to USB devices"
HOMEPAGE = "http://libusb.sf.net"
LICENSE = "LGPLv2.1"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools library

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/libusb-${PV}.tar.bz2;name=tar"

S = "${SRCDIR}/libusb-${PV}"

DEPENDS = "libpthread"

EXTRA_OECONF = "--disable-build-docs"

DEPENDS_${PN} += "libpthread libc"
RDEPENDS_${PN} += "libpthread libc"
