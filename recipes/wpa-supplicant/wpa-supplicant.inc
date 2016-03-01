DESCRIPTION = "A Client for Wi-Fi Protected Access (WPA)."
HOMEPAGE = "http://hostap.epitest.fi/wpa_supplicant/"
BUGTRACKER = "http://hostap.epitest.fi/bugz/"
require wpa-supplicant-configure.inc

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit make c++ pkgconfig

DEPENDS_LIBC = "libdl"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS += "libnl-3 libnl-genl-3 libnl-genl-3 librt \
	    ${CRYPTO} ${DEPENDS_LIBC}"

SRC_URI = "http://hostap.epitest.fi/releases/wpa_supplicant-${PV}.tar.gz \
           file://wpa-supplicant.sh \
           file://wpa_supplicant.conf \
           file://wpa_supplicant.conf-sane \
	   "

S = "${SRCDIR}/wpa_supplicant-${PV}/wpa_supplicant"

RDEPENDS_${PN} = "util/wpa-passphrase util/wpa-cli util/wpa-supplicant"

RECIPE_FLAGS += "readline"
WPA_SUPPLICANT_FLAGS:>USE_readline += " CONFIG_READLINE"
DEPENDS:>USE_readline += " libreadline libncurses"
RDEPENDS_${PN}-wpa-cli:>USE_readline += " libncurses libreadline"

RECIPE_FLAGS += "wpa_fast_eap"
WPA_SUPPLICANT_FLAGS:>USE_wpa_fast_eap += " CONFIG_EAP_FAST"
DEPENDS:>USE_wpa_fast_eap += " libssl"
RDEPENDS_${PN}-wpa-supplicant:>USE_wpa_fast_eap += " libssl"

RECIPE_FLAGS += "wpa_supplicant_wps"
WPA_SUPPLICANT_FLAGS:>USE_wpa_supplicant_wps += " CONFIG_WPS CONFIG_WPS2"

RECIPE_FLAGS += "wpa_supplicant_libnl"
DEFAULT_USE_wpa_supplicant_libnl = "1"
WPA_SUPPLICANT_FLAGS:>USE_wpa_supplicant_libnl += " CONFIG_LIBNL32"

RECIPE_FLAGS += "wpa_supplicant_gnutls"
DEFAULT_USE_wpa_supplicant_gnutls = "1"
WPA_SUPPLICANT_FLAGS:>USE_wpa_supplicant_gnutls += " CONFIG_TLS=gnutls"
CRYPTO:>USE_wpa_supplicant_gnutls = " libgnutls libgcrypt"
CRYPTO = " libssl libcrypto"

RECIPE_FLAGS += "wpa_supplicant_dbus"
DEFAULT_USE_wpa_supplicant_dbus = "1"
WPA_SUPPLICANT_FLAGS:>USE_wpa_supplicant_dbus += " CONFIG_CTRL_IFACE_DBUS CONFIG_CTRL_IFACE_DBUS_NEW"
DEPENDS:>USE_wpa_supplicant_dbus += " libdbus-1"

RECIPE_FLAGS += "wpa_supplicant_ap"
DEFAULT_USE_wpa_supplicant_ap = "1"
WPA_SUPPLICANT_FLAGS:>USE_wpa_supplicant_ap += " CONFIG_AP"

do_configure () {
	install -m 0755 defconfig .config
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
}

FILES_${PN} += "${datadir}/dbus-1/system-services/*"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "wpa_passphrase wpa_cli wpa_supplicant"
AUTO_PACKAGE_UTILS_DEPENDS += "libc"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc"
DEPENDS_${PN}-wpa-passphrase += " librt ${CRYPTO}"
RDEPENDS_${PN}-wpa-passphrase += " librt ${CRYPTO}"
DEPENDS_${PN}-wpa-cli += "librt"
RDEPENDS_${PN}-wpa-cli += "librt"
DEPENDS_${PN}-wpa-supplicant += "${DEPENDS_LIBC} ${CRYPTO} libnl-3 libnl-genl-3 librt"
RDEPENDS_${PN}-wpa-supplicant += "${DEPENDS_LIBC} ${CRYPTO} libnl-3 libnl-genl-3 librt"
DEPENDS_${PN}-wpa-supplicant:>USE_wpa_supplicant_dbus += " libdbus-1"
RDEPENDS_${PN}-wpa-supplicant:>USE_wpa_supplicant_dbus += " libdbus-1"

PACKAGES =+  "${PN}-conf"
FILES_${PN}-conf = "${sysconfdir}/wpa_supplicant.conf"
RDEPENDS_${PN}-wpa-supplicant += "${PN}-conf"
