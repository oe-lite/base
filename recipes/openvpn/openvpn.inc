# -*- mode:python; -*-
DESCRIPTION = "A full-featured SSL VPN solution via tun device."
HOMEPAGE = "http://openvpn.sourceforge.net"
LICENSE = "GPL-2.0"

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

inherit s6rc
SRC_URI += "\
  file://${PN}.hook \
  file://${PN}.run \
  file://${PN}-log.run \
  file://${PN}-log.notification-fd \
"

S6RC_LONGRUN_SERVICES += "openvpn-log"
RECIPE_FLAGS += "openvpn_s6rc_dependencies"
DEFAULT_USE_openvpn_s6rc_dependencies = "openvpn-log net"
do_install_s6[expand] = 3
do_install_s6() {
    mkdir -p "${D}${sysconfdir}/rc.hooks/${PN}@.d"
    install -m 0755 "${SRCDIR}/${PN}.hook" \
	    "${D}${sysconfdir}/rc.hooks/${PN}"
    install -m 0755 "${SRCDIR}/${PN}.run" \
	    "${D}${sysconfdir}/rc.hooks/${PN}@.d/run"
    echo longrun > "${D}${sysconfdir}/rc.hooks/${PN}@.d/type"
    for dep in ${USE_openvpn_s6rc_dependencies} ; do
        echo "$dep" >> "${D}${sysconfdir}/rc.hooks/${PN}@.d/dependencies"
    done
}
do_install[postfuncs] += "do_install_s6"
PACKAGES =+ "${PN}-s6"
FILES_${PN}-s6 = "${sysconfdir}/rc.hooks ${s6rcsrcdir}"
RDEPENDS_${PN}:>USE_s6rc += " ${PN}-s6"
