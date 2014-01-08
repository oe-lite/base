TARBALL_EXT = "gz"
require libpng.inc

DEPENDS_${PN} += "libm libz"

PROVIDES_${PN} += "libpng16"
PROVIDES_${PN}[qa] = "allow-missing-soname:libpng"
PROVIDES_${PN}-dev += "libpng16-dev"

PACKAGES += "${PN}-pngfix"
FILES_${PN}-pngfix = "${bindir}/pngfix ${bindir}/png-fix-itxt"
DEPENDS_${PN}-pngfix = "libc libm libpng16 libz"
RDEPENDS_${PN}-pngfix = "libc libm libpng16 libz"
