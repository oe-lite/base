DESCRIPTION = "DirectFB is a thin library that provides developers \
with hardware graphics acceleration, input device handling and \
abstraction, an integrated windowing system with support for \
translucent windows and multiple display layers on top of the \
Linux framebuffer device."
LICENSE = "LGPL"
HOMEPAGE = "http://directfb.org"

inherit autotools-autoreconf binconfig pkgconfig

DEPENDS = "jpeg-dev \
           libpng-dev \
           libpng-libpng12 \
           freetype-dev \
           libz \
           ${HOST_ARCH}/sysroot-libdl  \ 
           ${HOST_ARCH}/sysroot-libpthread  \ 
           ${HOST_ARCH}/sysroot-libm  \ 
           ${HOST_ARCH}/sysroot-libc  \ 
           ${HOST_ARCH}/sysroot-libstdc++  \ 
           tslib-dev"

SRC_URI = " \
    http://directfb.org/downloads/Core/DirectFB-1.4/DirectFB-${PV}.tar.gz \
   "

S = "${SRCDIR}/DirectFB-${PV}"

LDFLAGS_append =" -lts -lm"

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
  ${bindir}/directfb-config \
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
"
