DESCRIPTION = "PNG Library"
HOMEPAGE = "http://www.libpng.org/"
LICENSE = "libpng"

inherit autotools pkgconfig binconfig
BINCONFIG_GLOB = "${bindir}/libpng-config"

BBCLASSEXTEND = "native"

DEPENDS = "libz${RE} ${HOST_ARCH}/sysroot-libm"
DEPENDS_recipe-native = "libz${RE}"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.bz2"

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}-libpng3 ${PN}-libpng12 ${PN} ${PN}-doc"

PROVIDES_${PN}-libpng3="libpng3${RE}"
PROVIDES_${PN}-libpng12="libpng12${RE}"
RDEPENDS_${PN}-libpng3="${HOST_ARCH}/sysroot-libm libz"
RDEPENDS_${PN}-libpng12="${HOST_ARCH}/sysroot-libm libz"


FILES_${PN}-libpng3 = "${libdir}/libpng${SOLIBS}"
FILES_${PN}-libpng12 = "${libdir}/libpng12${SOLIBS}"

inherit library
