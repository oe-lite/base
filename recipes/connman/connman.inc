SUMMARY = "A daemon for managing internet connections within embedded devices"
DESCRIPTION = "The ConnMan project provides a daemon for managing \
internet connections within embedded devices running the Linux \
operating system.  The Connection Manager is designed to be slim and \
to use as few resources as possible, so it can be easily integrated. \
It is a fully modular system that can be extended, through plug-ins, \
to support all kinds of wired or wireless technologies. Also, \
configuration methods, like DHCP and domain name resolving, are \
implemented using plug-ins."
HOMEPAGE = "http://connman.net/"
BUGTRACKER = "https://01.org/jira/browse/CM"
LICENSE  = "GPL-2.0"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf pkgconfig

SRC_URI = "https://www.kernel.org/pub/linux/network/connman/connman-${PV}.tar.xz \
           file://connman \
           "

SRC_URI:>HOST_LIBC_musl += "file://0002-resolve-musl-does-not-implement-res_ninit.patch \
                            file://includes.patch"

CFLAGS:>HOST_LIBC_musl += " -D__GLIBC__"

EXTRA_OECONF += "\
    --enable-debug \
    --enable-loopback \
    --enable-ethernet \
    --disable-tools \
    --disable-polkit \
    --enable-client \
"

DEPENDS  = "libdbus-1 libglib-2.0 ppp iptables-dev libreadline"

FILES_${PN} += "${datadir}/dbus-1/system-services/*"

DEPENDS_${PN} += "libc libdbus-1 libdl libglib-2.0 libpcre libpthread libreadline libresolv librt libxtables"
RDEPENDS_${PN} += "libc libdbus-1 libdl libglib-2.0 libpcre libpthread libreadline libresolv librt libxtables"

RECIPE_FLAGS += "connman_gnutls"
EXTRA_OECONF += "${EXTRA_OECONF_GNUTLS}"
EXTRA_OECONF_GNUTLS = " --disable-wispr"
EXTRA_OECONF_GNUTLS:USE_connman_gnutls = " --enable-wispr"
DEPENDS:>USE_connman_gnutls += " libgnutls"
DEPENDS_${PN}:>USE_connman_gnutls += " libgmp libgnutls libhogweed libnettle libtasn1 libz"
RDEPENDS_${PN}:>USE_connman_gnutls += " libgmp libgnutls libhogweed libnettle libtasn1 libz"

RECIPE_FLAGS += "connman_wifi"
DEFAULT_USE_connman_wifi = "1"
EXTRA_OECONF += "${EXTRA_OECONF_WIFI}"
EXTRA_OECONF_WIFI = " --disable-wifi"
EXTRA_OECONF_WIFI:USE_connman_wifi = " --enable-wifi ac_cv_path_WPASUPPLICANT=${sbindir}/wpa_supplicant"
DEPENDS:>USE_connman_wifi += " util/wpa-supplicant"
DEPENDS_${PN}:>USE_connman_wifi += " util/wpa-supplicant"
RDEPENDS_${PN}:>USE_connman_wifi += " util/wpa-supplicant"

RECIPE_FLAGS += "connman_openvpn"
EXTRA_OECONF += "${EXTRA_OECONF_OPENVPN}"
EXTRA_OECONF_OPENVPN = "--disable-openvpn"
EXTRA_OECONF_OPENVPN:USE_connman_openvpn = "--enable-openvpn --with-openvpn=${sbindir}/openvpn"
DEPENDS:>USE_connman_openvpn += " openvpn"
DEPENDS_${PN}:>USE_connman_openvpn += " openvpn"
RDEPENDS_${PN}:>USE_connman_openvpn += " openvpn"

RECIPE_FLAGS += "connman_ofono"
EXTRA_OECONF += "${EXTRA_OECONF_OFONO}"
EXTRA_OECONF_OFONO = "--disable-ofono"
EXTRA_OECONF_OFONO:USE_connman_ofono = "--enable-ofono"
DEPENDS:>USE_connman_ofono += " ofono"
DEPENDS_${PN}:>USE_connman_ofono += " ofono"
RDEPENDS_${PN}:>USE_connman_ofono += " ofono"
