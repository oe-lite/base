
SRC_URI = "https://storage.googleapis.com/downloads.webmproject.org/releases/webp/libwebp-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit auto-package-libs auto-package-utils autotools

S = "${SRCDIR}/libwebp-${PV}"

DEPENDS += "libjpeg libpng libtiff libgif"

AUTO_PACKAGE_LIBS = "webp"

AUTO_PACKAGE_LIBS_DEPENDS = "libc libm libpthread webp-dev"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libm libpthread"

AUTO_PACKAGE_UTILS = "cwebp dwebp"
AUTO_PACKAGE_UTILS_DEPENDS = "libc libm libwebp libjpeg libpng libtiff"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libm libwebp libjpeg libpng libtiff"
