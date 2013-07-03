DESCRIPTION = "With FUSE it is possible to implement a fully functional filesystem in a userspace program"
HOMEPAGE = "http://fuse.sf.net"
LICENSE = "GPL"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig
DEPENDS = "libpthread librt libdl"
require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/fuse/fuse-${PV}.tar.gz"
