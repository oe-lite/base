DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"

inherit autotools-autoreconf auto-package-utils

DEPENDS += "librt"
RDEPENDS_${PN} += "librt target:gcc-sysroot-dbg"

SRC_URI = "http://www.valgrind.org/downloads/valgrind-${PV}.tar.bz2"

EXTRA_OECONF = "--enable-tls"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
