DESCRIPTION = "Serial port to network proxy"
HOMEPAGE = "http://sourceforge.net/projects/ser2net/"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf auto-package-utils

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.gz"
SRC_URI += "file://ser2net.conf.in"
SRC_URI += "file://ser2net.init"

RECIPE_FLAGS += "ser2net_config"
DEFAULT_USE_ser2net_config = "3001:telnet:0:/dev/ttyUSB0:115200 remctl banner1"

do_patch[postfuncs] += "do_patch_conf_file"
do_patch_conf_file() {
	echo ${USE_ser2net_config} >> ${SRCDIR}/ser2net.conf.in
}

do_install[postfuncs] += "do_install_extra_files"
do_install_extra_files() {
	sysvinit_install_script ${SRCDIR}/ser2net.init ser2net
	mkdir -p ${D}${sysconfdir}
	install -m 0644 ${SRCDIR}/ser2net.conf.in \
				${D}${sysconfdir}/ser2net.conf
}

inherit sysvinit
RECIPE_FLAGS += "ser2net_sysvinit_start ser2net_sysvinig_stop"
SYSVINIT_SCRIPT_ser2net = "ser2net"
DEFAULT_USE_ser2net_sysvinit_start = "98"
DEFAULT_USE_ser2net_sysvinit_stop  = "98"

FILES_${PN} += "/etc/ser2net.conf"

DEPENDS_${PN} = "libc"
RDEPENDS_${PN} = "libc"
