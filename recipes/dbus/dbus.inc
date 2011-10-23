# -*- mode:python; -*-
DESCRIPTION = "A message bus system for inter-process communication"
HOMEPAGE = "http://dbus.freedesktop.org"
LICENSE = "GPLv2+ AFLv2.1"

RECIPE_TYPES = "machine native"

inherit autotools pkgconfig gettext sysvinit

SRC_URI = "http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz"
SRC_URI += "file://dbus-1.init"

DEPENDS = "libexpat libglib libintl"

RECIPE_FLAGS += "dbus_x11"
EXTRA_OECONF_X11 = "--without-x"
EXTRA_OECONF_X11:USE_dbus_x11 = "--with-x"

EXTRA_OECONF = "\
  --disable-qt \
  --disable-qt3 \
  --disable-gtk \
  --disable-tests \
  --disable-checks \
  --disable-xml-docs \
  --disable-doxygen-docs \
  --disable-libaudit \
  --with-xml=expat \
  --with-dbus-default-reply-timeout=200000 \
  ${EXTRA_OECONF_X11} \
"

# On mipsel, D-Bus fails to link with --gc-sections and segfaults before main()
# when built with -fPIE/-pie.
do_configure[prefuncs] += "${DO_CONFIGURE_MIPSEL}"
DO_CONFIGURE_MIPSEL = ""
DO_CONFIGURE_MIPSEL:HOST_OS_mipsel = "do_configure_mipsel"
do_configure_mipsel() {
	sed -i -e 's/\-fPIE//' \
		-e 's/\-pie\ \-Wl\,\-z\,relro//' \
		-e 's/-Wl,--gc-sections//' \
		${S}/configure.in
}

do_install[postfuncs] =+ "do_install_extra_files"
do_install_extra_files() {
        sysvinit_install_script ${SRCDIR}/dbus-1.init dbus-1
	# the stock install seems to install the libtool wrapper
	# script, so we have to copy this manually :M:
	if [ -e bus/.libs/dbus-daemon-launch-helper ]; then
		install -d  ${D}${libexecdir}/
		install -m 0755 bus/.libs/dbus-daemon-launch-helper \
			${D}${libexecdir}/
	fi
}

RDEPENDS_${PN}-x11 = "${PN}"
PROVIDES_${PN} = "dbus-1"
RDEPENDS_${PN} += "libexpat libdbus"

PACKAGES =+ "${PN}-x11"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "dbus"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-1"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
FILES_${PN}-libdbus-dev = "${includedir}/dbus-1.0 ${libdir}/dbus-1.0/include"

FILES_${PN} = "\
	${bindir}/dbus-daemon* \
	${bindir}/dbus-uuidgen \
	${bindir}/dbus-cleanup-sockets \
	${bindir}/dbus-send \
	${bindir}/dbus-monitor \
	${libexecdir}/dbus* \
	${sysconfdir} \
	${datadir}/dbus-1/services \
	${datadir}/dbus-1/system-services \
"
FILES_${PN}-x11 = "${bindir}/dbus-launch"
FILES_${PN}-dev += "${libdir}/dbus-1.0/include ${bindir}/dbus-glib-tool ${libdir}/"

#pkg_postinst_${PN}() {
##!/bin/sh
## can't do adduser stuff offline
#if [ "x$D" != "x" ]; then
#  exit 1
#fi
#MESSAGEUSER=messagebus
#MESSAGEHOME=/var/run/dbus
#mkdir -p $MESSAGEHOME || true
#grep -q ^$MESSAGEUSER: /etc/group || addgroup "$MESSAGEUSER"
#chgrp "$MESSAGEUSER" "$MESSAGEHOME"
#grep -q ^$MESSAGEUSER: /etc/passwd || adduser --system --home "$MESSAGEHOME" --no-create-home --disabled-password --ingroup "$MESSAGEUSER" "$MESSAGEUSER"
#chown "$MESSAGEUSER"."$MESSAGEUSER" "$MESSAGEHOME"
#grep -q netdev: /etc/group || addgroup netdev
#chmod u+s /usr/libexec/dbus-daemon-launch-helper
#}

RECIPE_FLAGS += "dbus_sysvinit_start dbus_sysvinit_stop"
SYSVINIT_SCRIPT_dbus = "dbus-1"
DEFAULT_USE_dbus_sysvinit_start = "25"
DEFAULT_USE_dbus_sysvinit_stop = "25"
