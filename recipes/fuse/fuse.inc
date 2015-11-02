DESCRIPTION = "With FUSE it is possible to implement a fully functional filesystem in a userspace program"
HOMEPAGE = "http://fuse.sf.net"
LICENSE = "GPL"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig
DEPENDS = "libpthread librt libdl"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/fuse/fuse-${PV}.tar.gz"

PACKAGES = "${PN}-dbg ${PN} ${PN}-doc"

DEPENDS_${PN} = "libc libpthread"
RDEPENDS_${PN} = "libc libpthread"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "fuse ulockmgr"
LIBRARY_VERSION_${PN}-libfuse = "2"
LIBRARY_VERSION_${PN}-libulockmgr = "1"
DEPENDS_${PN}-libfuse = "libc libdl libpthread"
RDEPENDS_${PN}-libfuse = "libc libdl libpthread"
DEPENDS_${PN}-libulockmgr = "libc libpthread"
RDEPENDS_${PN}-libulockmgr = "libc libpthread"

FILES_${PN}-libfuse-dev = "${includedir}/fuse*"
FILES_${PN}-libulockmgr-dev = "${includedir}/ulockmgr.h"
