DESCRIPTION = "A message bus system for inter-process communication"
HOMEPAGE = "http://dbus.freedesktop.org"
LICENSE = "GPLv2+ AFLv2.1"

inherit autotools pkgconfig gettext sysvinit

DEPENDS = "expat${RE}-dev \
           glib${RE} \
           gettext${RE}-libintl"

SRC_URI = "http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz"
SRC_URI += "file://cross.patch"
SRC_URI += "file://tmpdir.patch"
SRC_URI += "file://fix-install-daemon.patch"
SRC_URI += "file://dbus-1.init"

S = "${SRCDIR}/dbus-${PV}"

EXTRA_OECONF_X = "--without-x"

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
  ${EXTRA_OECONF_X} \
"

# On mipsel, D-Bus fails to link with --gc-sections and segfaults before main()
# when built with -fPIE/-pie.
do_configure_prepend_mipsel() {
	sed -i -e 's/\-fPIE//' \
		-e 's/\-pie\ \-Wl\,\-z\,relro//' \
		-e 's/-Wl,--gc-sections//' \
		${S}/configure.in
}

do_install_append() {
        install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${SRCDIR}/dbus-1.init ${D}${sysconfdir}/init.d/dbus-1
        # the stock install seems to install the libtool wrapper script, so we have to copy this manually :M:
        if [ -e bus/.libs/dbus-daemon-launch-helper ]; then
                install -d  ${D}${libexecdir}/
                install -m 0755 bus/.libs/dbus-daemon-launch-helper ${D}${libexecdir}/
        fi
}

RDEPENDS_${PN}-x11 = "${PN}"
RRECOMMENDS_${PN}-lib = "${PN}"
RPROVIDES_${PN} = "dbus-1"

PACKAGES =+ "${PN}-lib ${PN}-x11"

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
FILES_${PN}-lib = "${libdir}/lib*.so.*"
FILES_${PN}-x11 = "\
${bindir}/dbus-launch \
"
FILES_${PN}-dev += "${libdir}/dbus-1.0/include ${bindir}/dbus-glib-tool ${libdir}/"

pkg_postinst_${PN}() {
#!/bin/sh
# can't do adduser stuff offline
if [ "x$D" != "x" ]; then
  exit 1
fi
MESSAGEUSER=messagebus
MESSAGEHOME=/var/run/dbus
mkdir -p $MESSAGEHOME || true
grep -q ^$MESSAGEUSER: /etc/group || addgroup "$MESSAGEUSER"
chgrp "$MESSAGEUSER" "$MESSAGEHOME"
grep -q ^$MESSAGEUSER: /etc/passwd || adduser --system --home "$MESSAGEHOME" --no-create-home --disabled-password --ingroup "$MESSAGEUSER" "$MESSAGEUSER"
chown "$MESSAGEUSER"."$MESSAGEUSER" "$MESSAGEHOME"
grep -q netdev: /etc/group || addgroup netdev
chmod u+s /usr/libexec/dbus-daemon-launch-helper
}

CONFFILES_${PN} = "${sysconfdir}/dbus-1/system.conf ${sysconfdir}/dbus-1/session.conf"

RECIPE_OPTIONS += "dbus-1_start dbus-1_stop"
SYSVINIT_SCRIPT_dbus-1 = "dbus-1"
DEFAULT_CONFIG_dbus-1_sysvinit_start = "25"
DEFAULT_CONFIG_dbus-1_sysvinit_stop = "25"
