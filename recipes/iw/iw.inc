DESCRIPTION = "nl80211 based CLI configuration utility for wireless devices"
HOMEPAGE = "http://linuxwireless.org/en/users/Documentation/iw"
LICENSE = "ISC"

COMPATIBLE_HOST_ARCHS = ".*linux"
inherit make c pkgconfig
DEPENDS = "libnl-3 libnl-nf-3 libnl-route-3 libnl-genl-3"
RDEPENDS_${PN} += "libnl-3 libnl-nf-3 libnl-route-3 libnl-genl-3"
PROVIDES_${PN} += "util/${PN}"
EXTRA_OEMAKE = "V=1"
SRC_URI = "https://www.kernel.org/pub/software/network/${PN}/${PN}-${PV}.tar.gz"

# git://git.sipsolutions.net/iw.git;protocol=git;${SRC_REV}
