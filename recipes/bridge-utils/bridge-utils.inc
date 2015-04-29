SUMMARY = "IEEE 802.1d ethernet bridging"
DESCRIPTION = "IEEE 802.1d ethernet bridging (plus Spanning Tree protocol) for the linux kernel. Kernel code is in Linux 2.4 and 2.6 kernels."

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/bridge/bridge-utils-${PV}.tar.gz"

inherit autotools-autoreconf

PROVIDES_${PN} += "util/brctl"
