# -*- mode:python; -*-
DESCRIPTION = "GLib is a general-purpose utility library, which provides many \
	useful data types, macros, type conversions, string utilities, file \
	utilities, a main loop abstraction, and so on. It works on many \
	UNIX-like platforms, Windows, OS/2 and BeOS."

inherit c++ autotools make-vpath

DEPENDS = "host-cross:gtk-doc libz libffi"

DEPENDS += "${DEPENDS_LIBELF}"
DEPENDS_LIBELF = "libelf"
DEPENDS_LIBELF:HOST_LIBC_mingw = ""
EXTRA_OECONF:>HOST_LIBC_mingw = " --disable-libelf"

DEPENDS += "${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:libglib native:libgthread native:libgmodule native:glib-utils"
DEPENDS_NATIVE:native = ""

DEPENDS += "${DEPENDS_LIBDL}"
DEPENDS_LIBDL = "libdl"
DEPENDS_LIBDL:HOST_OS_mingw32 = ""
DEPENDS_LIBDL:native = ""

DEPENDS += "${DEPENDS_LIBRESOLV}"
DEPENDS_LIBRESOLV = "libresolv"
DEPENDS_LIBRESOLV:HOST_OS_mingw32 = ""
DEPENDS_LIBRESOLV:native = ""

DEPENDS += "${DEPENDS_LIBINTL}"
DEPENDS_LIBINTL = ""
DEPENDS_LIBINTL:HOST_OS_mingw32 = "libintl"
DEPENDS_LIBINTL:HOST_KERNEL_darwin = "libintl"

require conf/fetch/gnome.conf
SRC_URI_SUBDIR = "${@'.'.join(d.getVar('PV', True).split('.')[:2])}"
SRC_URI = "${GNOME_MIRROR}/glib/${SRC_URI_SUBDIR}/glib-${PV}.tar.xz"
S = "${SRCDIR}/glib-${PV}"

EXTRA_OECONF = "--disable-debug \
	--disable-selinux \
	--disable-xattr \
	--disable-gtk-doc --disable-gtk-doc-html --disable-gtk-doc-pdf \
	--disable-man \
	--disable-modular-tests \
"

EXTRA_OEMAKE += "'CFLAGS=${CFLAGS}'"

do_install[postfuncs] += "do_install_unmangle"
do_install_unmangle() {
    sed -i -e s:${STAGE_DIR}/native${stage_bindir}:${bindir}:g \
        ${D}${bindir}/glib-mkenums || true
        rm -r ${D}${datadir}/bash-completion/completions/
}

PACKAGES =+ "${PN}-utils ${PN}-gdb"
FILES_${PN}-utils = "${bindir}/g*"
FILES_${PN}-gdb = "${datadir}/gdb ${datadir}/glib-2.0/gdb"
FILES_${PN}-doc += "${datadir}/gtk-doc"
FILES_${PN}-dev += "${datadir}/glib-2.0 ${libdir}/gdbus-2.0"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "glib gobject gmodule gthread gio"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:-2.0"
AUTO_PACKAGE_LIBS_RDEPENDS = "${PN}"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev_${PV}"

DEPENDS_ICONV = ""
DEPENDS_THREADS = ""
DEPENDS_FAM = ""
DEPENDS_PCRE = ""

DEPENDS_${PN} += "libffi"
DEPENDS_${PN}-utils += "${PN}-libgio"
DEPENDS_${PN}-libglib += "libc libgcc ${DEPENDS_PCRE} ${DEPENDS_LIBDL} ${DEPENDS_LIBINTL} ${DEPENDS_LIBRESOLV}"
DEPENDS_${PN}-libgthread += "libc libglib ${DEPENDS_THREADS} ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgobject += "libc libgcc libffi libglib libgthread ${DEPENDS_THREADS} ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgmodule += "libc ${DEPENDS_LIBDL} libglib ${DEPENDS_PCRE}"
DEPENDS_${PN}-libgio += "libc libgcc ${DEPENDS_LIBDL} ${DEPENDS_LIBRESOLV} libz libffi libglib libgmodule libgobject libgthread ${DEPENDS_PCRE} ${DEPENDS_THREADS}"

FILES_${PN}-libgio-dev = "${libdir}/pkgconfig/gio-*-2.0.pc"
FILES_${PN}-libgmodule-dev = "${libdir}/pkgconfig/gmodule-*-2.0.pc"
FILES_${PN} += "${libdir}/charset.alias"

include glib-${PV}.inc
