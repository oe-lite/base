DESCRIPTION = "A Client for Wi-Fi Protected Access (WPA)."
HOMEPAGE = "http://hostap.epitest.fi/wpa_supplicant/"
BUGTRACKER = "http://hostap.epitest.fi/bugz/"

inherit make c++ pkgconfig

LICENSE = "GPLv2 | BSD"

DEPENDS += "libdbus libgnutls libgnutls-extra libnl-3 libnl-genl-3 libnl-genl-3 libdl"

RDEPENDS_${PN} = "util/wpa-passphrase util/wpa-cli"

SRC_URI = "http://hostap.epitest.fi/releases/wpa_supplicant-${PV}.tar.gz \
           file://defconfig-gnutls \
           file://wpa-supplicant.sh \
           file://wpa_supplicant.conf \
           file://wpa_supplicant.conf-sane \
           file://99_wpa_supplicant \
	   "

export DBUS_LIBS="-ldbus-1"
export DBUS_INCLUDE="" 

S = "${SRCDIR}/wpa_supplicant-${PV}/wpa_supplicant"

RDEPENDS_${PN}-wpa-passphrase += "libgcrypt"
RDEPENDS_${PN} += "libgnutls libgnutls-extra libgcrypt libgpg-error libdbus"

do_configure () {
	install -m 0755 ${SRCDIR}/defconfig-gnutls .config
}

CFLAGS += "-I${HOST_SYSROOT}${includedir}/libnl3"
do_compile () {
	unset CPPFLAGS CXXFLAGS
	oe_runmake
}

do_install () {
	install -d ${D}${sbindir}
	install -m 755 wpa_supplicant ${D}${sbindir}
	install -m 755 wpa_cli        ${D}${sbindir}

	install -d ${D}${bindir}
	install -m 755 wpa_passphrase ${D}${bindir}

	install -d ${D}${docdir}/wpa_supplicant
	install -m 644 README ${SRCDIR}/wpa_supplicant.conf ${D}${docdir}/wpa_supplicant

	install -d ${D}${sysconfdir}
	install -m 600 ${SRCDIR}/wpa_supplicant.conf-sane ${D}${sysconfdir}/wpa_supplicant.conf

	install -d ${D}${sysconfdir}/network/if-pre-up.d/
	install -d ${D}${sysconfdir}/network/if-post-down.d/
	install -d ${D}${sysconfdir}/network/if-down.d/
	install -m 755 ${SRCDIR}/wpa-supplicant.sh ${D}${sysconfdir}/network/if-pre-up.d/wpa-supplicant
	cd ${D}${sysconfdir}/network/ && \
	ln -sf ../if-pre-up.d/wpa-supplicant if-post-down.d/wpa-supplicant

	install -d ${D}/${sysconfdir}/dbus-1/system.d
	install -m 644 ${S}/dbus/dbus-wpa_supplicant.conf ${D}/${sysconfdir}/dbus-1/system.d
	install -d ${D}/${datadir}/dbus-1/system-services
	install -m 644 ${S}/dbus/*.service ${D}/${datadir}/dbus-1/system-services
	sed -i -e s:${base_sbindir}:${sbindir}:g ${D}/${datadir}/dbus-1/system-services/*.service

	install -d ${D}/etc/default/volatiles
	install -m 0644 ${SRCDIR}/99_wpa_supplicant ${D}/etc/default/volatiles
}

FILES_${PN} += "${datadir}/dbus-1/system-services/*"
PROVIDES_${PN} = "util/wpa-supplicant"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "wpa_passphrase wpa_cli"
