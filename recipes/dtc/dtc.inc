SUMMARY = "Device Tree Compiler"
DESCRIPTION = "The Device Tree Compiler is a tool used to manipulate the Open-Firmware-like device tree used by PowerPC kernels."
LICENSE = "GPLv2 | BSD"
DEPENDS = "native:flex native:bison"

RECIPE_TYPES = "native sdk machine"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make

SRC_URI = "git://git.kernel.org/pub/scm/utils/dtc/dtc.git${SRCREV}"

S = "${SRCDIR}/dtc"

PACKAGES = "${PN}-dbg ${PN} ${PN}-misc"
FILES_${PN} = ""

# Yes, this looks a bit odd, but dtc Makefile uses $HOME as prefix to bin, lib
# and include dirs.
export HOME = "${prefix}"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "fdt"
LIBRARY_VERSION_dtc-libfdt = "1"
AUTO_PACKAGE_LIBS_DEPENDS = "libc"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc"
FILES_${PN}-libfdt += "${libdir}/libfdt-*${SOLIBSDEV}"
FILES_${PN}-libfdt-dev += "${includedir}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "dtc convert-dtsv0 dtdiff fdtdump fdtget fdtput"
AUTO_PACKAGE_UTILS_DEPENDS = "libfdt"
AUTO_PACKAGE_UTILS_RDEPENDS = "libfdt"
DEPENDS_${PN} = "${PN}-dtc ${PN}-fdtget ${PN}-fdtput"
RDEPENDS_${PN} = "${PN}-dtc ${PN}-fdtget ${PN}-fdtput"
DEPENDS_${PN}-misc = "${PN}-convert-dtsv0 ${PN}-fdtdump ${PN}-dtdiff"
RDEPENDS_${PN}-misc = "${PN}-convert-dtsv0 ${PN}-fdtdump ${PN}-dtdiff"
