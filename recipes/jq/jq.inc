SUMMARY = "jq is a lightweight and flexible command-line JSON processor"
HOMEPAGE = "https://stedolan.github.io/jq/"
LICENSE = "MIT"
SRC_URI = "https://github.com/stedolan/jq/releases/download/jq-${PV}/jq-${PV}.tar.gz"

RECIPE_TYPES = "machine native"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools

DEPS = "libc libm"
DEPENDS += "${DEPS}"
# The jq util does not depend on libjq.
DEPENDS_${PN} += "${DEPS}"
RDEPENDS_${PN} += "${DEPS}"
PROVIDES_${PN} += "util/${PN}"

inherit auto-package-libs

AUTO_PACKAGE_LIBS = "jq"
AUTO_PACKAGE_LIBS_DEPENDS = "${DEPS}"
AUTO_PACKAGE_LIBS_RDEPENDS = "${DEPS}"
FILES_jq-libjq-dev += "${includedir}"

EXTRA_OECONF += "--disable-maintainer-mode"
