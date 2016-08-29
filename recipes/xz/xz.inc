DESCRIPTION = "Free general-purpose data compression software"
HOMEPAGE = "http://tukaani.org/xz/"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine native"

# The COPYING file starts
#
#   Different licenses apply to different files in this package. Here
#   is a rough summary of which licenses apply to which parts of this
#   package (but check the individual files to be sure!):
#
# The main binaries and the library are in the public domain. The
# *diff, *cmp, *grep wrappers are based on code from gzip and are
# under GPLv2+. That covers the files that actually end up on target,
# hence this license tag:

LICENSE = "GPL-2.0+ & Public Domain"

SRC_URI = "http://tukaani.org/xz/xz-${PV}.tar.bz2"

inherit autotools c auto-package-libs auto-package-utils

DEPENDS += "libpthread"

AUTO_PACKAGE_LIBS = "lzma"
AUTO_PACKAGE_LIBS_DEPENDS = "libc libpthread xz-dev"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libpthread"

AUTO_PACKAGE_UTILS = " \
  lzmadec  \
  lzmainfo \
  xz       \
  xzdec    \
  xzdiff   \
  xzgrep   \
  xzless   \
  xzmore   \
"

AUTO_PACKAGE_UTILS_DEPENDS += "libc libpthread liblzma"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc libpthread liblzma"

# The binaries come with a few symlinks. Put these alongside the
# binary they point to.
AUTO_PACKAGE_UTILS_SYMLINKS_xz = "lzcat lzma unlzma unxz xzcat"
AUTO_PACKAGE_UTILS_SYMLINKS_xzdiff = "lzcmp lzdiff xzcmp"
AUTO_PACKAGE_UTILS_SYMLINKS_xzgrep = "lzegrep lzfgrep lzgrep xzegrep xzfgrep"
AUTO_PACKAGE_UTILS_SYMLINKS_xzless = "lzless"
AUTO_PACKAGE_UTILS_SYMLINKS_xzmore = "lzmore"

