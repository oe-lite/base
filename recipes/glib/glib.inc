DESCRIPTION = "GLib is a general-purpose utility library, \
which provides many useful data types, macros, \
type conversions, string utilities, file utilities, a main \
loop abstraction, and so on. It works on many \
UNIX-like platforms, Windows, OS/2 and BeOS."
LICENSE = "LGPLv2+"

BBCLASSEXTEND = "native"

inherit autotools-autoreconf gettext auto-package-libs

DEPENDS = "glib-native-dev libglib-native libgmodule-native \
    glib-native-utils \
    gtk${RE}-doc-dev libz \
    ${TARGET_ARCH}/sysroot-libpthread \
    ${TARGET_ARCH}/sysroot-libdl \
    ${TARGET_ARCH}/sysroot-libresolv \
    ${TARGET_ARCH}/sysroot-libstdc++ \
"

DEPENDS_recipe-native = "gettext-native-dev \
    gtk-doc-native-dev pkg-config-native-dev"

require conf/fetch/gnome.conf
SRC_URI_SUBDIR = "${@".".join(d.getVar('PV', True).split(".")[:2])}"
SRC_URI = "${GNOME_MIRROR}/glib/${SRC_URI_SUBDIR}/${BP}.tar.bz2"

SRC_URI += "file://config.site"
SRC_HOST_SITEFILES = "${SRCDIR}/config.site"

EXTRA_OECONF = "--disable-debug"

# Add and entry for your favourite arch if your (g)libc has a sane printf
#EXTRA_OECONF_append_glibc_arm += "--enable-included-printf=no"

EXTRA_OECONF_ipv6 = ""
EXTRA_OECONF_ipv6_RECIPE_OPTION_ipv6 = "--disable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_ipv6}"

EXTRA_OEMAKE_append = "'CFLAGS=${CFLAGS}'"

do_install_append() {
    sed -i -e s:${STAGE_DIR}/native/bin:${bindir}:g \
        ${D}${bindir}/glib-mkenums || true
}

PACKAGES =+ "${PN}-utils"
FILES_${PN}-utils = "${bindir}/*"

AUTO_PACKAGE_LIBS = "glib gobject gmodule gthread gio"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-2.0"

AUTO_PACKAGE_LIBS_DEV_DEPENDS += "glib${RE}-dev"
RDEPENDS_${PN}-libgthread += "${PN}-libglib ${TARGET_ARCH}/sysroot-libpthread"
RDEPENDS_${PN}-libgobject += "${PN}-libgthread"
RDEPENDS_${PN}-libgmodule += "${PN}-libglib"
RDEPENDS_${PN}-libgio     += "${PN}-libgobject libz ${TARGET_ARCH}/sysroot-libresolv ${TARGET_ARCH}/sysroot-libdl"

EXTRA_FILES_${PN}-libgio-dev = "${libdir}/pkgconfig/gio-*-2.0.pc"
EXTRA_FILES_${PN}-libgmodule-dev = "${libdir}/pkgconfig/gmodule-*-2.0.pc"
