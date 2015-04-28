DESCRIPTION = "A small utility for examining and tuning the settings \
of your ethernet-based network interfaces."
HOMEPAGE = "http://www.kernel.org/pub/software/network/ethtool/"
LICENSE = "GPL"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/software/network/ethtool/${P}.tar.gz"

