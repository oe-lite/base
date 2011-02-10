DESCRIPTION = "Very high-quality data compression program"
SECTION = "console/utils"
LICENSE = "bzip2"

BBCLASSEXTEND = "native"

inherit autotools pkgconfig auto-package-libs

SRC_URI = "http://www.bzip.org/${PV}/bzip2-${PV}.tar.gz"

AUTO_PACKAGE_LIBS = "bz2"
EXTRA_FILES_${PN}-libbz2-dev = "${includedir} ${libdir}/pkgconfig/bzip2.pc"

RDEPENDS_${PN} = "${PN}-libbz2"

do_configure_prepend () {
    bash ./autogen.sh
}
