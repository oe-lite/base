DESCRIPTION = "GIFLIB is a package of portable tools and library routines for working with GIF images."
HOMEPAGE = "http://giflib.sourceforge.net/"
LICENSE = "MIT"

SRC_URI = "http://kent.dl.sourceforge.net/project/giflib/giflib-${PV}.tar.bz2"

inherit autotools library auto-package-utils
LIBRARY_NAME = "libgif"

DEPENDS += "libc libm"
DEPENDS_${PN} += "libc libm"

AUTO_PACKAGE_UTILS = "\
  gif2rgb   \
  gifbuild  \
  gifecho   \
  giffix    \
  gifinto   \
  giftext   \
  giftool   \
  gifclrmp  \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libm libgif"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libm libgif"
