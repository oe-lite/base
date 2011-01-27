DESCRIPTION = "Valgrind memory debugger"
HOMEPAGE = "http://valgrind.org/"
BUGTRACKER = "http://valgrind.org/support/bug_reports.html"
LICENSE = "GPLv2+ & BSD & FDLv1.2"

inherit autotools

SRC_URI = "http://www.valgrind.org/downloads/valgrind-${PV}.tar.bz2"

EXTRA_OECONF = "--enable-tls"

EXTRA_OEMAKE = "-w"

FILES_${PN}-dbg += "${libdir}/${PN}/*/.debug/*"
