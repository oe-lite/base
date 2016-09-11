SECTION = "console/network"
DESCRIPTION = "Iperf is a tool to measure maximum TCP bandwidth, allowing the tuning of various parameters and UDP characteristics"
HOMEPAGE = "http://iperf.fr/"
LICENSE = "iperf"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools c++

SRC_URI = "git://github.com/esnet/iperf.git;protocol=http;tag=${PV}"

S = "${SRCDIR}/iperf"

RDEPENDS_${PN} += "libstdc++"
