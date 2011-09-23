require libpng.inc

inherit library

DEPENDS_${PN} += "libm libz"
PACKAGES =+ "${PN}-libpng3"
FILES_${PN}-libpng3 = "${libdir}/libpng.so.3*"
PROVIDES_${PN}-libpng3 = "libpng3"
DEPENDS_${PN}-libpng3 += "libm libz"
PROVIDES_${PN}-dev += "libpng3-dev"

PROVIDES_${PN} = "libpng12"
PROVIDES_${PN}-dev = "libpng12-dev"
