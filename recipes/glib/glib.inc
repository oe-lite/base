# -*- mode:python; -*-
DESCRIPTION = "GLib is a general-purpose utility library, which provides many \
	useful data types, macros, type conversions, string utilities, file \
	utilities, a main loop abstraction, and so on. It works on many \
	UNIX-like platforms, Windows, OS/2 and BeOS."
LICENSE = "LGPLv2+"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf gettext auto-package-libs

DEPENDS = "native:libglib native:libgmodule native:glib-utils \
    native:gtk-doc libz libpthread libdl libresolv libstdc++"

DEPENDS:native = "gtk-doc libz libpthread libdl libresolv libstdc++"

require conf/fetch/gnome.conf
SRC_URI_SUBDIR = "${@'.'.join(d.getVar('PV', True).split('.')[:2])}"
SRC_URI = "${GNOME_MIRROR}/glib/${SRC_URI_SUBDIR}/${P}.tar.bz2"

SRC_URI += "file://config.site"
SRC_HOST_SITEFILES = "${SRCDIR}/config.site"

EXTRA_OECONF = "--disable-debug"

# Add and entry for your favourite arch if your (g)libc has a sane printf
#EXTRA_OECONF_append_glibc_arm += "--enable-included-printf=no"

RECIPE_FLAGS += "ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"
EXTRA_OECONF_IPV6 = "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_ipv6 = ""

EXTRA_OEMAKE_append = "'CFLAGS=${CFLAGS}'"

do_install[postfuncs] += "do_install_unmangle"
do_install_unmangle() {
    sed -i -e s:${STAGE_DIR}/native${stage_bindir}:${bindir}:g \
        ${D}${bindir}/glib-mkenums || true
}

PACKAGES =+ "${PN}-utils"
FILES_${PN}-utils = "${bindir}/*"

AUTO_PACKAGE_LIBS = "glib gobject gmodule gthread gio"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-2.0"

AUTO_PACKAGE_LIBS_DEV_DEPENDS += ""
DEPENDS_${PN}-libgthread = "libglib libpthread"
DEPENDS_${PN}-libgobject = "libglib libgthread"
DEPENDS_${PN}-libgmodule = "libglib"
DEPENDS_${PN}-libgio     = "libglib libgobject libz libresolv libdl"

#FILES_${PN}-libgio-dev = "${libdir}/pkgconfig/gio-*-2.0.pc"
#FILES_${PN}-libgmodule-dev = "${libdir}/pkgconfig/gmodule-*-2.0.pc"
