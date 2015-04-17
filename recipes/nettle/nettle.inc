DESCRIPTION = "The Nettle package contains the low-level cryptographic \
	library that is designed to fit easily in many contexts"
LICENSE = "LGPL-2.1+"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/${PN}/${PN}-${PV}.tar.gz"

inherit c++ autotools

DEPENDS += "libgmp"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "nettle hogweed"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
DEPENDS_${PN}-dev = ""
DEPENDS_${PN}-libnettle += "libc libgcc"
DEPENDS_${PN}-libhogweed += "libc libgmp libnettle"
RDEPENDS_${PN}-libhogweed += "libc libgmp libnettle"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "nettle-hash nettle-lfib-stream pkcs1-conv sexp-conv"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libnettle libgmp"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libnettle libgmp"

DEPENDS_${PN}-pkcs1-conv += "libhogweed"
RDEPENDS_${PN}-pkcs1-conv += "libhogweed"

DEPENDS_${PN} += "libgmp libc libnettle"
RDEPENDS_${PN} += "libgmp libc libnettle"
