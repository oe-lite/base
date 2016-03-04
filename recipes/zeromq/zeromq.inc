inherit autotools pkgconfig c++ auto-package-utils auto-package-libs

RECIPE_TYPES = "machine sdk"

DESCRIPTION = "Zeromq - The Intelligent Transport Layer"
HOMEPAGE = "http://www.zeromq.org"
LICENSE = "LGPLv3+"
SRC_URI = "http://download.zeromq.org/zeromq-${PV}.tar.gz"

COMMON_DEPENDS = "libc libgcc libm libpthread libstdc++"
COMMON_RDEPENDS = "libc libgcc libm libpthread libstdc++"
DEPENDS += "${COMMON_DEPENDS} ${DEPENDS_LIBSODIUM}"

AUTO_PACKAGE_UTILS = "curve_keygen"
AUTO_PACKAGE_UTILS_DEPENDS += "${COMMON_DEPENDS} libzmq"
AUTO_PACKAGE_UTILS_RDEPENDS += "${COMMON_RDEPENDS} libzmq"

AUTO_PACKAGE_LIBS = "zmq"
AUTO_PACKAGE_LIBS_DEPENDS += "${COMMON_DEPENDS} ${DEPENDS_LIBSODIUM}"
AUTO_PACKAGE_LIBS_RDEPENDS += "${COMMON_RDEPENDS} ${DEPENDS_LIBSODIUM}"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev_${PV}"
LIBRARY_VERSION = "5"

RECIPE_FLAGS += "zeromq_libsodium"
DEPENDS_LIBSODIUM = "libsodium"
DEPENDS_LIBSODIUM:USE_zeromq_libsodium = "libsodium"
EXTRA_OECONF_LIBSODIUM = "--without-libsodium"
EXTRA_OECONF_LIBSODIUM:USE_zeromq_libsodium = "--with-libsodium"
EXTRA_OECONF += "${EXTRA_OECONF_LIBSODIUM}"
