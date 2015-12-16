DESCRIPTION = "User space daemon for extended IEEE 802.11 management"
HOMEPAGE = "http://hostap.epitest.fi"
LICENSE = "GPLv2 BSD"
DEPENDS = "libnl-3 libnl-genl-3 openssl librt"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit make

SRC_URI = " \
    http://hostap.epitest.fi/releases/hostapd-${PV}.tar.gz \
    file://defconfig \
    file://init \
"

S = "${SRCDIR}/hostapd-${PV}/hostapd"

do_configure() {
    install -m 0644 ${SRCDIR}/defconfig ${S}/.config
}

CFLAGS = "-MMD -O2 -Wall -g -I${MACHINE_SYSROOT}${includedir}/libnl3"

do_install() {
    install -d ${D}${sbindir} ${D}${sysconfdir}/init.d
    install -m 0644 ${S}/hostapd.conf ${D}${sysconfdir}
    install -m 0755 ${S}/hostapd ${D}${sbindir}
    install -m 0755 ${S}/hostapd_cli ${D}${sbindir}
    install -m 755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/hostapd
}

DEPENDS_${PN} = "libc libcrypto libnl-3 libnl-genl-3 librt libssl"
RDEPENDS_${PN} = "libc libcrypto libnl-3 libnl-genl-3 librt libssl"
