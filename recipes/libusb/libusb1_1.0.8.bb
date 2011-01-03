DESCRIPTION = "library to provide userspace access to USB devices"
HOMEPAGE = "http://libusb.sf.net"
SECTION = "libs"
LICENSE = "LGPLv2.1"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/libusb-${PV}.tar.bz2;name=tar"
S = "${SRCDIR}/libusb-${PV}"

DEPENDS = "${TARGET_ARCH}/sysroot-libpthread"

inherit autotools

EXTRA_OECONF = "--disable-build-docs"
