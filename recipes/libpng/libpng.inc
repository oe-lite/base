DESCRIPTION = "PNG Library"
HOMEPAGE = "http://www.libpng.org/"
LICENSE = "libpng"

inherit autotools pkgconfig library binconfig
BINCONFIG_GLOB = "${bindir}/libpng-config"

RECIPE_TYPES = "machine native sdk"

DEPENDS = "libz libm"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.bz2"
