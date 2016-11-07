DESCRIPTION = "This software provides support for the Tag Image File Format (TIFF)"
HOMEPAGE = "http://www.simplesystems.org/libtiff/"
LICENSE = "BSD-2-Clause*"

RECIPE_TYPES = "machine native"
SRC_URI = "ftp://download.osgeo.org/libtiff/tiff-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools c++ auto-package-utils auto-package-libs
AUTOCONFDIRS = "/config"

RECIPE_FLAGS += "tiff_jpeg tiff_lzma tiff_zlib"
DEFAULT_USE_tiff_jpeg = "1"
DEFAULT_USE_tiff_lzma = "1"
DEFAULT_USE_tiff_zlib = "1"

# The configure script autodetects presence of lib{jpeg,lzma,z} and
# enables/disables accordingly. So in principle one can control these
# features via what gets staged. However, that's somewhat fragile and
# non-obvious, so we pass explicit --disable flags to configure,
# appending corresponding --enable flags only if the USE flag is set.

EXTRA_OECONF += "--disable-jpeg --disable-lzma --disable-zlib"
TIFF_JPEG = ""
TIFF_JPEG:USE_tiff_jpeg = "libjpeg"
EXTRA_OECONF:>USE_tiff_jpeg = " --enable-jpeg"
TIFF_LZMA = ""
TIFF_LZMA:USE_tiff_lzma = "liblzma"
EXTRA_OECONF:>USE_tiff_lzma = " --enable-lzma"
TIFF_ZLIB = ""
TIFF_ZLIB:USE_tiff_zlib = "libz"
EXTRA_OECONF:>USE_tiff_zlib = " --enable-zlib"

USE_FLAG_DEPENDS = "${TIFF_JPEG} ${TIFF_LZMA} ${TIFF_ZLIB}"

DEPENDS += "libc libgcc-s libm libstdc++ ${USE_FLAG_DEPENDS}"

AUTO_PACKAGE_UTILS = "\
  bmp2tiff    \
  fax2ps      \
  fax2tiff    \
  gif2tiff    \
  pal2rgb     \
  ppm2tiff    \
  ras2tiff    \
  raw2tiff    \
  rgb2ycbcr   \
  thumbnail   \
  tiff2bw     \
  tiff2pdf    \
  tiff2ps     \
  tiff2rgba   \
  tiffcmp     \
  tiffcp      \
  tiffcrop    \
  tiffdither  \
  tiffdump    \
  tiffinfo    \
  tiffmedian  \
  tiffset     \
  tiffsplit   \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libm libtiff ${USE_FLAG_DEPENDS}"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libm libtiff ${USE_FLAG_DEPENDS}"

AUTO_PACKAGE_LIBS = "tiff tiffxx"
AUTO_PACKAGE_LIBS_DEPENDS = "libc libm tiff-dev ${USE_FLAG_DEPENDS}"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libm ${USE_FLAG_DEPENDS}"
DEPENDS_${PN}-libtiffxx += "libgcc-s libstdc++ libtiff"
RDEPENDS_${PN}-libtiffxx += "libgcc-s libstdc++ libtiff"
