DESCRIPTION = "PNG Library"
HOMEPAGE = "http://www.libpng.org/"
LICENSE = "libpng"

inherit autotools pkgconfig binconfig

BBCLASSEXTEND = "native"

DEPENDS = "zlib-dev ${HOST_ARCH}/sysroot-libm"
DEPENDS_recipe-native = "zlib-native-dev"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libpng/libpng-${PV}.tar.bz2"

S = "${SRCDIR}/libpng-${PV}"

PACKAGES =+ "${PN}-libpng3 ${PN}-libpng12"

PROVIDES_${PN}-libpng3="libpng3${RE}"
PROVIDES_${PN}-libpng12="libpng12${RE}"

FILES_${PN}-libpng3 = "${libdir}/libpng.so.*"
FILES_${PN}-libpng12 = "${libdir}/libpng12.so.*"
FILES_${PN}-dev = "${includedir} ${libdir}/lib*.so ${libdir}/*.la \
		${libdir}/*.a ${libdir}/pkgconfig \
		${datadir}/aclocal ${bindir} ${sbindir}"

