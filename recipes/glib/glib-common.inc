# -*- mode:python; -*-
DESCRIPTION = "GLib is a general-purpose utility library, which provides many \
	useful data types, macros, type conversions, string utilities, file \
	utilities, a main loop abstraction, and so on. It works on many \
	UNIX-like platforms, Windows, OS/2 and BeOS."

inherit c++ autotools

DEPENDS = "host-cross:gtk-doc libz libpthread libdl libresolv \
	libffi ${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:libglib native:libgmodule native:glib-utils"
DEPENDS_NATIVE:native = ""

require conf/fetch/gnome.conf
SRC_URI_SUBDIR = "${@'.'.join(d.getVar('PV', True).split('.')[:2])}"
SRC_URI = "${GNOME_MIRROR}/glib/${SRC_URI_SUBDIR}/glib-${PV}.tar.bz2"
S = "${SRCDIR}/glib-${PV}"

EXTRA_OECONF = "--disable-debug \
	--disable-selinux \
	--disable-xattr \
	--disable-gtk-doc --disable-gtk-doc-html --disable-gtk-doc-pdf \
	--disable-man \
"

EXTRA_OEMAKE += "'CFLAGS=${CFLAGS}'"

do_install[postfuncs] += "do_install_unmangle"
do_install_unmangle() {
    sed -i -e s:${STAGE_DIR}/native${stage_bindir}:${bindir}:g \
        ${D}${bindir}/glib-mkenums || true
}

PACKAGES =+ "${PN}-utils ${PN}-gdb"
FILES_${PN}-utils = "${bindir}/*"
FILES_${PN}-gdb = "${datadir}/gdb ${datadir}/glib-2.0/gdb"
FILES_${PN}-doc += "${datadir}/gtk-doc"
FILES_${PN}-dev += "${datadir}/glib-2.0"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "glib gobject gmodule gthread gio"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-2.0"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"

DEPENDS_ICONV = ""
DEPENDS_THREADS = ""
DEPENDS_FAM = ""
DEPENDS_PCRE = ""

DEPENDS_${PN} += "libffi"
DEPENDS_${PN}-libglib = "libc libgcc ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgthread = "libc libglib ${DEPENDS_THREADS} ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgobject = "libc libffi libglib libgthread ${DEPENDS_THREADS} ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgmodule = "libc libdl libglib ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgio     = "libc libgcc libdl libresolv libz libffi libglib libgmodule libgobject libgthread ${DEPENDS_PCRE} ${DEPENDS_THREADS}"

FILES_${PN}-libgio-dev = "${libdir}/pkgconfig/gio-*-2.0.pc"
FILES_${PN}-libgmodule-dev = "${libdir}/pkgconfig/gmodule-*-2.0.pc"
FILES_${PN} += "${libdir}/gdbus-2.0"
