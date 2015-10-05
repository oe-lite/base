DESCRIPTION = "Database Independent Abstraction Layer for C"
HOMEPAGE = "http://libdbi.sourceforge.net/"
LICENSE = "LGPLv2.1+"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libdbi/libdbi-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS = ".*linux"

DEPENDS += "libm libdl"
RDEPENDS_${PN} += "libm libdl"
DEPENDS_${PN} += "libm libdl"

inherit autotools

EXTRA_OECONF = "--disable-docs"
