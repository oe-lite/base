DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"

inherit autotools-autoreconf auto-package-utils

DEPENDS += "librt"
RDEPENDS_${PN} += "librt ld-so-dbg"

DEPENDS_${PN}-cg-merge = "libc"
RDEPENDS_${PN}-cg-merge = "libc"

DEPENDS_${PN}-valgrind-listener = "libc"
RDEPENDS_${PN}-valgrind-listener = "libc"

DEPENDS_${PN} += "libc libpthread"

SRC_URI = "ftp://sourceware.org/pub/valgrind/valgrind-${PV}.tar.bz2"
SRC_URI:>TARGET_CPU_arm += " file://arm-cortex-support.patch"
SRC_URI:>TARGET_CPU_arm += "file://0001-wire-up-sys_splice-for-arm.patch"

EXTRA_OECONF = "--enable-tls"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
FILES_${PN}-dev += "${libdir}/${PN}/*.a"
