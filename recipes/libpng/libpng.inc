DESCRIPTION = "PNG Library"
HOMEPAGE = "http://www.libpng.org/"
LICENSE = "libpng"

inherit autotools make-vpath pkgconfig library binconfig
BINCONFIG_GLOB = "${bindir}/libpng-config"

RECIPE_TYPES = "machine native sdk"

DEPENDS = "libz libm"
DEPENDS_${PN} += "libc"

require conf/fetch/sourceforge.conf
TARBALL_EXT ?= "bz2"
SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.${TARBALL_EXT}"
