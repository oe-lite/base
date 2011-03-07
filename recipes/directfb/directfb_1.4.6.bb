require directfb.inc

DEPENDS += "sysfsutils"

SRC_URI += "file://directfb-1.2.x-fix-pkgconfig-cflags.patch"
SRC_URI += "file://mkdfiff.patch"

EXTRA_OECONF = "\
  --enable-freetype=yes \
  --enable-zlib \
  --with-gfxdrivers=none \
  --disable-sdl \
  --disable-vnc \
  --disable-x11 \
"
LEAD_SONAME = "libdirectfb-1.4.so.5"
