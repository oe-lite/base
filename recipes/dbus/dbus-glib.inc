# -*- mode:python; -*-
DESCRIPTION = "GLib bindings for the dbus message bus system"
HOMEPAGE = "http://www.freedesktop.org/Software/dbus"

RECIPE_TYPES = "machine native"

inherit autotools-autoreconf pkgconfig gettext

SRC_URI = "http://dbus.freedesktop.org/releases/dbus-glib/dbus-glib-${PV}.tar.gz"

DEPENDS = "libexpat libintl librt libdbus \
           libgobject libglib libgthread libgmodule"

DEPENDS += "${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:dbus-glib"
DEPENDS_NATIVE:native = ""

DEPENDS += "native:glib-utils"

EXTRA_OECONF += "${EXTRA_OECONF_DBUS_BINDING_TOOL}"
EXTRA_OECONF_DBUS_BINDING_TOOL = "--with-dbus-binding-tool=${STAGE_DIR}/native/bin/dbus-binding-tool"
EXTRA_OECONF_DBUS_BINDING_TOOL:native = ""

FILES_${PN}-doc += "${datadir}/gtk-doc/html/dbus-glib"

DEPENDS_${PN} = "libc libpthread librt libpcre libglib libgobject \
	libgthread libffi libexpat libdbus libdbus-glib"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "dbus-glib"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-1"
FILES_${PN}-libdbus-glib-dev = "${includedir}"
DEPENDS_${PN}-libdbus-glib = "libc libpthread librt libpcre libglib libgobject \
	libgthread libffi libdbus"
