DESCRIPTION = "A small utility for examining and tuning the settings \
of your ethernet-based network interfaces."
HOMEPAGE = "https://ftp.kernel.org/pub/software/network/ethtool/"
SECTION = "console/network"
LICENSE = "GPL"

inherit autotools

SRC_URI = "https://ftp.kernel.org/pub/software/network/ethtool/${BPN}-${PV}.tar.gz"

