DESCRIPTION = "hdparm is a Linux shell utility for viewing \
and manipulating various IDE drive and driver parameters."
SECTION = "console/utils"
LICENSE = "BSD"
LICENSE_${PN}-wiper = "GPL-2.0"
inherit c make

PACKAGES =+ "${PN}-wiper"
PROVIDES_${PN}-wiper += "util/wiper"

FILES_${PN}-wiper = "${sbindir}/wiper.sh"

RDEPENDS_${PN}-wiper = "bash util/awk util/stat"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/hdparm/hdparm-${PV}.tar.gz "

EXTRA_OEMAKE += 'STRIP="echo"'
EXTRA_OEMAKE_INSTALL = 'sbindir=${sbindir}'

do_install[postfuncs] += "do_install_wipe"
do_install_wipe () {
	install -m 0755 ${S}/wiper/wiper.sh ${D}/${sbindir}
}
