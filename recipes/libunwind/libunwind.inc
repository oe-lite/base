DESCRIPTION = "a portable and efficient C programming interface (API) to determine the call-chain of a program"
LICENSE = "MIT"

RECIPE_TYPES = "machine native"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf auto-package-libs library

SRC_URI = "git://git.sv.gnu.org/libunwind.git;tag=v${PV}"
S = "${SRCDIR}/libunwind"

AUTO_PACKAGE_LIBS = "arm setjmp coredump generic ptrace"

DEPENDS_${PN} += "ld-so libc libgcc-s libunwind-arm"
RDEPENDS_${PN} += "ld-so libc libgcc-s libunwind-arm"
PROVIDES_${PN} = "libunwind-8 libunwind"

DEPENDS_${PN}-libptrace += "libc libgcc-s"
RDEPENDS_${PN}-libptrace += "libc libgcc-s"
PROVIDES_${PN}-libptrace += "libunwind-ptrace libunwind-ptrace-0"
PROVIDES_${PN}-libptrace[qa] = "allow-missing-soname:libptrace"
FILES_${PN}-libptrace = "${sharedlibdir}/libunwind-ptrace.so*"
FILES_${PN}-libarm = "${sharedlibdir}/libunwind-arm.so*"
FILES_${PN}-libsetjmp = "${sharedlibdir}/libunwind-setjmp.so*"
FILES_${PN}-libcoredump = "${sharedlibdir}/libunwind-coredump.so*"
FILES_${PN}-libgeneric = "${sharedlibdir}/libunwind-generic.so*"
