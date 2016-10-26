SUMMARY = "System call tracing tool"
HOMEPAGE = "http://strace.sourceforge.net"
LICENSE = "BSD"

COMPATIBLE_HOST_ARCHS = ".*linux"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/strace/strace-${PV}.tar.xz"

inherit autotools auto-package-utils

AUTO_PACKAGE_UTILS = "strace strace-graph strace-log-merge"
RDEPENDS_${PN}-strace-graph += "perl"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc ${PN}-strace"
