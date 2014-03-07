DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"

inherit autotools-autoreconf auto-package-utils

DEPENDS += "librt"
RDEPENDS_${PN} += "librt"

DEPENDS_${PN}-cg-merge = "libc"
RDEPENDS_${PN}-cg-merge = "libc"

DEPENDS_${PN}-valgrind-listener = "libc"
RDEPENDS_${PN}-valgrind-listener = "libc"

DEPENDS_${PN} += "libc libpthread"

SRC_URI = "http://www.valgrind.org/downloads/valgrind-${PV}.tar.bz2"

EXTRA_OECONF = "--enable-tls"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
FILES_${PN}-dev += "${libdir}/${PN}/*.a"
