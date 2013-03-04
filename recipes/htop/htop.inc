DESCRIPTION = "htop process monitor"
HOMEPAGE = "http://htop.sf.net"
LICENSE = "GPLv2"

inherit autotools
require conf/fetch/sourceforge.conf

DEPENDS += "ncurses libm"
RDEPENDS_${PN} += "ncurses"

SRC_URI = "${SOURCEFORGE_MIRROR}/htop/htop-${PV}.tar.gz"

EXTRA_OECONF +=" --disable-unicode --disable-native-affinity"

FILES_${PN} += " ${datadir}/applications/htop.desktop"
FILES_${PN} += " ${datadir}/pixmaps/htop.png"
