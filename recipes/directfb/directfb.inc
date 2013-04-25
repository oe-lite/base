# -*- mode:python; -*-

DESCRIPTION = "DirectFB is a thin library that provides developers \
with hardware graphics acceleration, input device handling and \
abstraction, an integrated windowing system with support for \
translucent windows and multiple display layers on top of the \
Linux framebuffer device."
LICENSE = "LGPL"
HOMEPAGE = "http://directfb.org"

inherit c++ autotools-autoreconf make-vpath pkgconfig binconfig

DEPENDS = "libjpeg \
	libpng12 \
	libfreetype \
	libz \
	libdl \
	libpthread \
	libm  \
	libc  \
	libts"

RDEPENDS_${PN} = "libjpeg \
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

FILES_${PN}-dbg += "\
	${libdir}/directfb-${RV}/*/*/.debug/*.so \
	${libdir}/directfb-${RV}/*/.debug/*.so \
"

PACKAGES += "${PN}-internal ${PN}-internal-dev"
FILES_${PN}-internal += "\
	${libdir}/directfb-${RV}/*/*.so \
	${libdir}/directfb-${RV}/*/*/*.so \
	${datadir}/directfb-${PV} \
"
FILES_${PN}-internal-dev += "\
	${libdir}/directfb-${RV}/*/*.la \
	${libdir}/directfb-${RV}/*/*/*.la \
"

inherit auto-package-libs
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-1.4,"
AUTO_PACKAGE_LIBS = "direct directfb fusion"
DEPENDS_${PN}-libdirect = "libgcc libc libdl libpthread libm libts libz"
DEPENDS_${PN}-fusion = "libc libdl libpthread libm libts libz libdirect"
DEPENDS_${PN}-libdirectfb = "libgcc libc libdl libpthread libm libts libz libdirect libfusion"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "dfbdump dfbfx dfbg dfbinfo dfbinput dfbinspector \
	dfblayer dfbmaster dfbpenmount dfbscreen directfb-csource \
	mkdfiff mkdgiff mkdgifft"

AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev"
