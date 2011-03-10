DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"
BUGTRACKER = "http://valgrind.org/support/bug_reports.html"
LICENSE = "GPLv2+ & BSD & FDLv1.2"

inherit autotools

DEPENDS += "${HOST_ARCH}/sysroot-librt"
RDEPENDS_${PN} += "${HOST_ARCH}/sysroot-librt ${HOST_ARCH}/sysroot-dbg"

SRC_URI = "http://www.valgrind.org/downloads/valgrind-${PV}.tar.bz2"
SRC_URI += "file://vg-ppc-feature.patch"

EXTRA_OECONF = "--enable-tls"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
