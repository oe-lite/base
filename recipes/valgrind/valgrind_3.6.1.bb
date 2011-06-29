DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"
BUGTRACKER = "http://valgrind.org/support/bug_reports.html"
LICENSE = "GPLv2+ & BSD & FDLv1.2"

inherit autotools auto-package-utils

DEPENDS += "${HOST_ARCH}/sysroot-librt"
RDEPENDS_${PN} += "${HOST_ARCH}/sysroot-librt ${HOST_ARCH}/sysroot-dbg"

SRC_URI = "http://www.valgrind.org/downloads/valgrind-${PV}.tar.bz2"
SRC_URI += "file://vg-ppc-feature.patch"

EXTRA_OECONF = "--enable-tls"

AUTO_PACKAGE_UTILS = "callgrind_annotate callgrind_control cg_annotate \
                      cg_diff cg_merge ms_print valgrind-listener \
                      no_op_client_for_valgrind"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
