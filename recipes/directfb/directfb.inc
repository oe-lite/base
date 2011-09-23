DESCRIPTION = "DirectFB is a thin library that provides developers \
with hardware graphics acceleration, input device handling and \
abstraction, an integrated windowing system with support for \
translucent windows and multiple display layers on top of the \
Linux framebuffer device."
LICENSE = "LGPL"
HOMEPAGE = "http://directfb.org"

inherit autotools-autoreconf pkgconfig library binconfig

DEPENDS = "libjpeg \
	libpng12 \
	libfreetype \
	libz \
	libdl \
	libpthread \
	libm  \
	libc  \
	libstdc++ \
	libts"

RDEPENDS = "libjpeg \
	libpng12 \
	freetype \
	libz \
	libdl \
	libpthread \
	libm  \
	libc  \
	libstdc++ \
	libts"

SRC_URI = "http://directfb.org/downloads/Core/DirectFB-1.4/DirectFB-${PV}.tar.gz"
S = "${SRCDIR}/DirectFB-${PV}"

LDFLAGS +="-lts -lm"

EXTRA_OECONF = "\
  --with-gfxdrivers=none \
  --enable-libmpeg3=no \
  --enable-freetype=yes \
  --enable-sdl=no \
  --enable-vnc=no \
  --disable-x11 \
"

do_install() {
        oe_runmake 'DESTDIR=${D}' install
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-dev ${PN} ${PN}-locale"

FILES_${PN}-dbg += "\
  ${libdir}/directfb-${RV}/*/*/.debug/*.so \
  ${libdir}/directfb-${RV}/*/.debug/*.so \
"

FILES_${PN}-dev += "\
  ${libdir}/directfb-${RV}/systems/*.la \
  ${libdir}/directfb-${RV}/inputdrivers/*.la \
  ${libdir}/directfb-${RV}/interfaces/*/*.la \
  ${libdir}/directfb-${RV}/wm/*.la \
"

FILES_${PN} += "\
  ${libdir}/directfb-${RV}/systems/*.so \
  ${libdir}/directfb-${RV}/inputdrivers/*.so \
  ${libdir}/directfb-${RV}/interfaces/*/*.so \
  ${libdir}/directfb-${RV}/wm/*.so \
  ${datadir}/directfb-${PV} \
  ${bindir} \
"

# FIXME: shouldn't we be providing libdirectfb and libdirectfb-dev ???
