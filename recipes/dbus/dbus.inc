# -*- mode:python; -*-
DESCRIPTION = "A message bus system for inter-process communication"
HOMEPAGE = "http://dbus.freedesktop.org"
LICENSE = "GPLv2+ AFLv2.1"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath pkgconfig gettext sysvinit passwd c++

SRC_URI = "http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz"
SRC_URI += "file://dbus-1.init"
SRC_URI += "file://passwd file://group"

DEPENDS = "libexpat libglib libintl"

DEPENDS += "${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread librt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

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
        install -m 0755 -d ${D}${localstatedir}/run/dbus
}

RDEPENDS_${PN}-x11 = "${PN}"
RDEPENDS_${PN} += "libc ${DEPENDS_LIBC} libexpat libdbus"
RDEPENDS_${PN}-x11 += "libc ${DEPENDS_LIBC}"

PACKAGES =+ "${PN}-x11"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "dbus-1"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc libpthread librt ${PN}-dev"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libpthread librt"

RECIPE_FLAGS += "dbus_sysvinit_start dbus_sysvinit_stop"
SYSVINIT_SCRIPT_dbus = "dbus-1"
DEFAULT_USE_dbus_sysvinit_start = "25"
DEFAULT_USE_dbus_sysvinit_stop = "25"

inherit splashutils-progress
RECIPE_FLAGS += "dbus_1_splashutils_progress dbus_1_splashutils_msg"
SPLASHUTILS_INITSCRIPTS = "dbus_1"
DEFAULT_USE_dbus_1_splashutils_msg = "\"Starting Dbus\""

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "dbus-cleanup-sockets dbus-daemon dbus-launch \
			dbus-monitor dbus-run-session dbus-send dbus-uuidgen"
AUTO_PACKAGE_UTILS_DEPENDS += "libc"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc"
DEPENDS_${PN}-dbus-daemon += "libexpat libpthread librt"
RDEPENDS_${PN}-dbus-daemon += "libexpat libpthread librt"
DEPENDS_${PN}-dbus-monitor += "libdbus-1"
RDEPENDS_${PN}-dbus-monitor += "libdbus-1"
DEPENDS_${PN}-dbus-run-session += "libdbus-1"
RDEPENDS_${PN}-dbus-run-session += "libdbus-1"
DEPENDS_${PN}-dbus-send += "libdbus-1"
RDEPENDS_${PN}-dbus-send += "libdbus-1"
DEPENDS_${PN}-dbus-uuidgen += "libdbus-1"
RDEPENDS_${PN}-dbus-uuidgen += "libdbus-1"

#To be removed in next base master release!
PROVIDES_${PN}-libdbus-1 += "libdbus"
PROVIDES_${PN}-libdbus-1-dev += "libdbus-dev"
PROVIDES_${PN}-libdbus-1[qa] += "allow-missing-soname:libdbus"
