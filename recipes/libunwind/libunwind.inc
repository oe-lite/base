DESCRIPTION = "a portable and efficient C programming interface (API) to determine the call-chain of a program"
LICENSE = "MIT"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = "arm-.*linux"

inherit autotools-autoreconf auto-package-libs library

SRC_URI = "git://git.sv.gnu.org/libunwind.git;tag=v${PV}"
S = "${SRCDIR}/libunwind"

AUTO_PACKAGE_LIBS = "arm setjmp coredump ptrace"

AUTO_PACKAGE_LIBS_DEPENDS = "libc libgcc ${PN}"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libgcc ${PN}"

AUTO_PACKAGE_LIBS_PROVIDEPREFIX = "${PN}-"
AUTO_PACKAGE_LIBS_PKGPREFIX = ""
AUTO_PACKAGE_LIBS_LIBPREFIX = "${PN}-"

DEPENDS_${PN} += "ld-so libc libgcc"
RDEPENDS_${PN} += "ld-so libc libgcc"

DEPENDS_${PN}-setjmp += "libunwind libunwind-arm"
RDEPENDS_${PN}-setjmp += "libunwind libunwind-arm"

PACKAGES += "${PN}-full"
RDEPENDS_${PN}-full += "${LIBS_AUTO_RPACKAGES}"
