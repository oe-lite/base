# -*- mode:python; -*-
DESCRIPTION = "A full-featured SSL VPN solution via tun device."
HOMEPAGE = "http://openvpn.sourceforge.net"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig

SRC_URI = "http://build.openvpn.net/downloads/releases/openvpn-${PV}.tar.xz"

DEPENDS = "libdl liblzo2 libssl libcrypto"

inherit sysvinit
RECIPE_FLAGS += "openvpn_sysvinit_start openvpn_sysvinit_stop"

SRC_URI += "file://openvpn.init"
do_install[postfuncs] =+ "do_install_openvpn_extra"
do_install_openvpn_extra () {
	install -d ${D}/${sysconfdir}/openvpn
	sysvinit_install_script ${SRCDIR}/openvpn.init openvpn
}

DEPENDS_${PN} = "libc libgcc ${DEPENDS}"
RDEPENDS_${PN} = "libc libgcc ${DEPENDS}"

FILES_${PN}-dev += "${libdir}/openvpn/plugins/*.la"
FILES_${PN}-dbg += "${libdir}/openvpn/plugins/.debug"
