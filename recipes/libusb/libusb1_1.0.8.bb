DESCRIPTION = "library to provide userspace access to USB devices"
HOMEPAGE = "http://libusb.sf.net"
LICENSE = "LGPLv2.1"

inherit autotools library

DEPENDS = "${TARGET_ARCH}/sysroot-libpthread"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libusb/libusb-${PV}.tar.bz2;name=tar \
           file://fix_missing_librt.patch"
S = "${SRCDIR}/libusb-${PV}"

EXTRA_OECONF = "--disable-build-docs"

RDEPENDS_${PN} = "${TARGET_ARCH}/sysroot-libpthread ${TARGET_ARCH}/sysroot-librt"
DEPENDS_${PN}-dev += "${TARGET_ARCH}/sysroot-libpthread ${TARGET_ARCH}/sysroot-librt"
