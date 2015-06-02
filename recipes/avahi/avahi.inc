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

LICENSE = "GPLv2+ & LGPLv2.1+"

DEPENDS = "libc libgcc libexpat libcap libdaemon libdbus-1 libglib-2.0 libgobject-2.0"
DEPENDS += "${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread librt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

#Patches copied from yocto
SRC_URI = "http://avahi.org/download/avahi-${PV}.tar.gz \
          file://00avahi-autoipd \
          file://99avahi-autoipd \
          file://initscript.patch \
          file://avahi_fix_install_issue.patch \
          file://fix_for_automake_1.12.x.patch \
          file://out-of-tree.patch \
          file://0001-avahi-fix-avahi-status-command-error-prompt.patch \
          file://reuseport-check.patch \
          file://passwd file://group \
          "

inherit autotools pkgconfig gettext c++ c sysvinit passwd

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
             ${AVAHI_GTK} \
           "

AVAHI_GTK ?= "--disable-gtk --disable-gtk3"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "avahi-common avahi-core avahi-client avahi-glib avahi-gobject"

inherit auto-package-utils

AUTO_PACKAGE_UTILS = "daemon dnsconfd autoipd utils"

#FILES_avahi = ""
DEPENDS_${PN} += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
RDEPENDS_${PN} += "avahi-daemon libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
FILES_${PN}-autoipd = "${sbindir}/avahi-autoipd \
                       ${sysconfdir}/avahi/avahi-autoipd.action \
                       ${sysconfdir}/dhcp/*/avahi-autoipd \
                       ${sysconfdir}/udhcpc.d/00avahi-autoipd \
                       ${sysconfdir}/udhcpc.d/99avahi-autoipd"
DEPENDS_${PN}-autoipd += "libc libdaemon"
RDEPENDS_${PN}-autoipd += "libc libdaemon"
FILES_${PN}-libavahi-common = "${libdir}/libavahi-common.so.*"
DEPENDS_${PN}-libavahi-common += "libc libpthread"
RDEPENDS_${PN}-libavahi-common += "libc libpthread"
FILES_${PN}-libavahi-core = "${libdir}/libavahi-core.so.*"
DEPENDS_${PN}-libavahi-core += "libavahi-common libc libpthread"
RDEPENDS_${PN}-libavahi-core += "libavahi-common libc libpthread"
FILES_${PN}-daemon = "${sbindir}/avahi-daemon \
                      ${sysconfdir}/avahi/avahi-daemon.conf \
                      ${sysconfdir}/avahi/hosts \
                      ${sysconfdir}/avahi/services \
                      ${sysconfdir}/dbus-1 \
                      ${sysconfdir}/init.d/avahi-daemon \
                      ${datadir}/avahi/introspection/*.introspect \
                      ${datadir}/avahi/avahi-service.dtd \
                      ${datadir}/avahi/service-types \
                      ${datadir}/dbus-1/system-services \
                      ${datadir}/dbus-1/*"
DEPENDS_${PN}-daemon += "libavahi-common libavahi-core libc libcap libdaemon libdbus libdl libexpat libpthread"
RDEPENDS_${PN}-daemon += "libavahi-common libavahi-core libc libcap libdaemon libdbus libdl libexpat libpthread"
FILES_${PN}-libavahi-client = "${libdir}/libavahi-client.so.*"
DEPENDS_${PN}-libavahi-client += "libavahi-common libc libdbus libdl libpthread"
RDEPENDS_${PN}-libavahi-client += "libavahi-common libc libdbus libdl libpthread"
FILES_${PN}-dnsconfd = "${sbindir}/avahi-dnsconfd \
                        ${sysconfdir}/avahi/avahi-dnsconfd.action \
                        ${sysconfdir}/init.d/avahi-dnsconfd"
DEPENDS_${PN}-dnsconfd += "libavahi-common libc libdaemon libpthread"
RDEPENDS_${PN}-dnsconfd += "libavahi-common libc libdaemon libpthread"
FILES_${PN}-libavahi-glib = "${libdir}/libavahi-glib.so.*"
DEPENDS_${PN}-libavahi-glib += "libavahi-common libc libglib libpcre libpthread"
RDEPENDS_${PN}-libavahi-glib += "libavahi-common libc libglib libpcre libpthread"
FILES_${PN}-libavahi-gobject = "${libdir}/libavahi-gobject.so.*"
DEPENDS_${PN}-libavahi-gobject += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
RDEPENDS_${PN}-libavahi-gobject += "libavahi-client libavahi-common libavahi-glib libc libdbus libdl libffi libglib libgobject libpcre libpthread"
FILES_${PN}-utils = "${bindir}/avahi-*"
DEPENDS_${PN}-utils += "libavahi-client libavahi-common libc libdbus libdl libpthread"
RDEPENDS_${PN}-utils += "libavahi-client libavahi-common libc libdbus libdl libpthread"
