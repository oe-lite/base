SUMMARY = "Device Tree Compiler"
DESCRIPTION = "The Device Tree Compiler is a tool used to manipulate the Open-Firmware-like device tree used by PowerPC kernels."
LICENSE = "GPLv2 | BSD"
DEPENDS = "native:flex native:bison"

RECIPE_TYPES = "native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make

SRC_URI = "git://www.jdl.com/software/dtc.git;protocol=git${SRCREV}"

S = "${SRCDIR}/dtc"

PACKAGES =+ "${PN}-misc"
FILES_${PN}-misc = "${bindir}/convert-dtsv0 ${bindir}/ftdump ${bindir}/dtdiff"
FILES_${PN}-dev += "/include"
