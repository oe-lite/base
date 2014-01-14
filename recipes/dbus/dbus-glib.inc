# -*- mode:python; -*-
DESCRIPTION = "GLib bindings for the dbus message bus system"
HOMEPAGE = "http://www.freedesktop.org/Software/dbus"

RECIPE_TYPES = "machine native"

inherit autotools-autoreconf pkgconfig gettext

SRC_URI = "http://dbus.freedesktop.org/releases/dbus-glib/dbus-glib-${PV}.tar.gz"

DEPENDS = "libexpat libintl ${DEPENDS_LIBC} libdbus-1 \
	libgobject libglib libgthread libgmodule"
DEPENDS_LIBC = "librt libpthread"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

DEPENDS += "${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:dbus-glib"
DEPENDS_NATIVE:native = ""

DEPENDS += "native:glib-utils"

EXTRA_OECONF += "${EXTRA_OECONF_DBUS_BINDING_TOOL}"
EXTRA_OECONF_DBUS_BINDING_TOOL = "--with-dbus-binding-tool=${STAGE_DIR}/native/bin/dbus-binding-tool"
EXTRA_OECONF_DBUS_BINDING_TOOL:native = ""

FILES_${PN}-doc += "${datadir}/gtk-doc/html/dbus-glib"

DEPENDS_${PN} = "libc ${DEPENDS_LIBC} libpcre libglib libgobject \
	libgthread libffi libexpat libdbus-1 libdbus-glib-1"
RDEPENDS_${PN} = "libc ${DEPENDS_LIBC} libpcre libglib libgobject \
	libgthread libffi libexpat libdbus-1 libdbus-glib-1"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "dbus-glib-1"
FILES_${PN}-libdbus-glib-1-dev = "${includedir}"
DEPENDS_${PN}-libdbus-glib-1 = "libc ${DEPENDS_LIBC} libpcre libglib \
	libgobject libgthread libffi libdbus-1 libgio"

#To be removed in next base master release!
PROVIDES_${PN}-libdbus-glib-1 += "libdbus-glib"
PROVIDES_${PN}-libdbus-glib-1-dev += "libdbus-glib-dev"
PROVIDES_${PN}-libdbus-glib-1[qa] += "allow-missing-soname:libdbus-glib"
