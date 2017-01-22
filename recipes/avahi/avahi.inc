# -*- mode:python; -*-
DESCRIPTION = "Avahi is a fully LGPL framework for Multicast DNS Service Discovery. It \
allows programs to publish and discover services and hosts running on a local network \
with no specific configuration. This tool implements IPv4LL, Dynamic Configuration of \
IPv4 Link-Local Addresses (IETF RFC3927), a protocol for automatic IP address \
configuration from the link-local 169.254.0.0/16 range without the need for a central \
server."
AUTHOR = "Lennart Poettering <lennart@poettering.net>"
HOMEPAGE = "http://avahi.org"

RECIPE_TYPES = "machine"

COMPATIBLE_HOST_ARCHS = ".*linux"

LICENSE = "GPLv2+ & LGPLv2.1+"

DEPENDS = "libc libgcc libexpat libcap libdaemon libdbus-1 libglib-2.0 libgobject-2.0"
DEPENDS += "${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread librt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

#Patches copied from yocto
SRC_URI = "https://github.com/lathiat/${PN}/releases/download/v${PV}/${P}.tar.gz \
          file://00avahi-autoipd \
          file://99avahi-autoipd \
          file://initscript.patch \
          file://daemon-passwd file://daemon-group \
          file://autoipd-passwd file://autoipd-group \
          file://autoipd-init \
          "

inherit autotools-autoreconf pkgconfig gettext c++ c sysvinit passwd
PASSWD_FILES = "${SRCDIR}/autoipd-passwd ${SRCDIR}/daemon-passwd"
GROUP_FILES = "${SRCDIR}/autoipd-group ${SRCDIR}/daemon-group"
DEPENDS += "native:glib-utils"

RECIPE_FLAGS += "avahi-compat-libdns-sd"
LIBDNSSD = "--disable-compat-libdbs_sd"
LIBDNSSD:USE_avahi-compat-libdns-sd = "--enable-compat-libdns_sd"

# libdns-sd is also provided by mdnssd
PRIORITY:USE_avahi-compat-libdns-sd = "9"
LIBDNSSD_INSTALL = ""
LIBDNSSD_INSTALL:USE_avahi-compat-libdns-sd = "do_install_dns_sd"

EXTRA_OECONF = "--disable-introspection \
             --with-avahi-priv-access-group=adm \
             --disable-stack-protector \
             --disable-gdbm \
             --disable-mono \
             --disable-monodoc \
             --disable-qt3 \
             --disable-qt4 \
             --disable-python \
             --disable-doxygen-doc \
             --with-distro=debian \
             ${LIBDNSSD} \
             ${AVAHI_GTK} \
           "

AVAHI_GTK ?= "--disable-gtk --disable-gtk3"

RECIPE_FLAGS += "avahi-daemon_sysvinit_start avahi-daemon_sysvinit_stop"
SYSVINIT_SCRIPT_avahi-daemon = "avahi-daemon"
DEFAULT_USE_avahi-daemon_sysvinit_start = "26"
DEFAULT_USE_avahi-daemon_sysvinit_stop = "26"

RECIPE_FLAGS += "avahi-autoipd_sysvinit_start avahi-autoipd_sysvinit_stop"
SYSVINIT_SCRIPT_avahi-autoipd = "avahi-autoipd"
DEFAULT_USE_avahi-autoipd_sysvinit_start = "27"
DEFAULT_USE_avahi-autoipd_sysvinit_stop = "27"

RECIPE_FLAGS += "avahi-autoipd_network_interface"
DEFAULT_USE_avahi-autoipd_network_interface = "eth0"

do_install[postfuncs] =+ "do_install_extra_files ${LIBDNSSD_INSTALL}"
do_install_extra_files() {
    sed -e 's%^INTERFACE=".*%INTERFACE="${USE_avahi-autoipd_network_interface}"%' -i ${SRCDIR}/autoipd-init
        sysvinit_install_script ${SRCDIR}/avahi-${PV}/initscript/debian/avahi-daemon avahi-daemon
        sysvinit_install_script ${SRCDIR}/autoipd-init avahi-autoipd
}

do_install_dns_sd() {
    ln -s avahi-compat-libdns_sd/dns_sd.h ${D}${includedir}/dns_sd.h
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS += "avahi-common avahi-core avahi-client avahi-glib avahi-gobject"
AUTO_PACKAGE_LIBS:>USE_avahi-compat-libdns-sd += " dns_sd"

inherit auto-package-utils

AUTO_PACKAGE_UTILS = "${PN}-daemon ${PN}-dnsconfd ${PN}-autoipd ${PN}-utils"

#split out configuration, to allow downstream override
PACKAGES =+ "${PN}-daemon-config"

#FILES_avahi = ""
DEPENDS_${PN} += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
RDEPENDS_${PN} += "avahi-avahi-daemon libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
FILES_${PN}-${PN}-autoipd = "${sbindir}/avahi-autoipd \
                       ${sysconfdir}/avahi/avahi-autoipd.action \
                       ${sysconfdir}/dhcp/*/avahi-autoipd \
                       ${sysconfdir}/udhcpc.d/00avahi-autoipd \
                       ${sysconfdir}/udhcpc.d/99avahi-autoipd \
                       ${sysconfdir}/rc*.d/*-autoipd \
                       ${sysconfdir}/init.d/*-autoipd \
                       ${passwddir}/${PN}/autoipd-passwd \
                       ${groupdir}/${PN}/autoipd-group \
"
DEPENDS_${PN}-${PN}-autoipd += "libc libdaemon"
RDEPENDS_${PN}-${PN}-autoipd += "libc libdaemon"
FILES_${PN}-libavahi-common = "${libdir}/libavahi-common.so.*"
DEPENDS_${PN}-libavahi-common += "libc libpthread"
RDEPENDS_${PN}-libavahi-common += "libc libpthread"
FILES_${PN}-libavahi-core = "${libdir}/libavahi-core.so.*"
DEPENDS_${PN}-libavahi-core += "libavahi-common libc libpthread"
RDEPENDS_${PN}-libavahi-core += "libavahi-common libc libpthread"
FILES_${PN}-${PN}-daemon = "${sbindir}/avahi-daemon \
                      ${sysconfdir}/avahi/hosts \
                      ${sysconfdir}/avahi/services \
                      ${sysconfdir}/dbus-1 \
                      ${sysconfdir}/init.d/avahi-daemon \
                      ${datadir}/avahi/introspection/*.introspect \
                      ${datadir}/avahi/avahi-service.dtd \
                      ${datadir}/avahi/service-types \
                      ${datadir}/dbus-1/system-services \
                      ${datadir}/dbus-1/* \
                      ${sysconfdir}/rc*.d/*-daemon \
                      ${passwddir}/${PN}/daemon-passwd \
                      ${groupdir}/${PN}/daemon-group \
"
DEPENDS_${PN}-${PN}-daemon += "libavahi-common libavahi-core libc libcap libdaemon libdbus libdl libexpat libpthread"
RDEPENDS_${PN}-${PN}-daemon += "${PN}-daemon-config libavahi-common libavahi-core libc libcap libdaemon libdbus libdl libexpat libpthread"
FILES_${PN}-libavahi-client = "${libdir}/libavahi-client.so.*"
DEPENDS_${PN}-libavahi-client += "libavahi-common libc libdbus libdl libpthread"
RDEPENDS_${PN}-libavahi-client += "libavahi-common libc libdbus libdl libpthread"
FILES_${PN}-${PN}-dnsconfd = "${sbindir}/avahi-dnsconfd \
                        ${sysconfdir}/avahi/avahi-dnsconfd.action \
                        ${sysconfdir}/init.d/avahi-dnsconfd"
DEPENDS_${PN}-${PN}-dnsconfd += "libavahi-common libc libdaemon libpthread"
RDEPENDS_${PN}-${PN}-dnsconfd += "libavahi-common libc libdaemon libpthread"
FILES_${PN}-libavahi-glib = "${libdir}/libavahi-glib.so.*"
DEPENDS_${PN}-libavahi-glib += "libavahi-common libc libglib libpcre libpthread"
RDEPENDS_${PN}-libavahi-glib += "libavahi-common libc libglib libpcre libpthread"
FILES_${PN}-libavahi-gobject = "${libdir}/libavahi-gobject.so.*"
DEPENDS_${PN}-libavahi-gobject += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
RDEPENDS_${PN}-libavahi-gobject += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
FILES_${PN}-${PN}-utils = "${bindir}/avahi-*"
DEPENDS_${PN}-${PN}-utils += "libavahi-client libavahi-common libc libdbus libdl libpthread"
RDEPENDS_${PN}-${PN}-utils += "libavahi-client libavahi-common libc libdbus libdl libpthread"

FILES_${PN}-daemon-config = "${sysconfdir}/avahi/avahi-daemon.conf"

FILES_${PN}-libdns-sd += "${libdir}/libdns_sd.so*"
DEPENDS_${PN}-libdns-sd += "libavahi-client libavahi-common libc libdbus libdl ${PN}-dev"
RDEPENDS_${PN}-libdns-sd += "libavahi-client libavahi-common libc libdbus libdl"
PROVIDES_${PN}-libdns-sd = "libdns-sd-1"
