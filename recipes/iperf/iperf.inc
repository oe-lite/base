SECTION = "console/network"
DESCRIPTION = "Iperf is a tool to measure maximum TCP bandwidth, allowing the tuning of various parameters and UDP characteristics"
HOMEPAGE = "http://iperf.fr/"
LICENSE = "iperf"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools c++
require conf/fetch/sourceforge.conf

SRC_URI = "${SOURCEFORGE_MIRROR}/iperf/iperf-${PV}.tar.gz"

RDEPENDS_${PN} += "libstdc++"
