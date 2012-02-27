require libpng.inc

DEPENDS_${PN} += "libm libz"
PROVIDES_${PN} += "libpng15"
PROVIDES_${PN}-dev += "libpng15-dev"
