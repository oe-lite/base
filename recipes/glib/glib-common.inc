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
#gELF in glib not compatible with aarch64
EXTRA_OECONF:>TARGET_CPU_aarch64 = " --disable-libelf"

DEPENDS += "${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:libglib-2.0 native:libgthread-2.0 \
		native:libgmodule-2.0 native:glib-utils"
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
AUTO_PACKAGE_LIBS = "glib-2.0 gobject-2.0 gmodule-2.0 gthread-2.0 gio-2.0"
AUTO_PACKAGE_LIBS_RDEPENDS = "${PN}"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev_${PV}"

DEPENDS_ICONV = ""
DEPENDS_THREADS = ""
DEPENDS_FAM = ""
DEPENDS_PCRE = ""

DEPENDS_${PN} += "libffi"
DEPENDS_${PN}-utils += "libgio-2.0 libglib-2.0 libgmodule-2.0 libgobject-2.0 \
				libelf"
RDEPENDS_GLIB_UTILS = "libc libdl libffi libgio-2.0 libgmodule-2.0 \
			libgoject-2.0 libpcre libpthread libresolv libz"
RDEPENDS_GLIB_UTILS:native = ""
RDEPENDS_${PN}-utils = "${RDEPENDS_GLIB_UTILS}"
DEPENDS_${PN}-libglib-2.0 += "libc libgcc ${DEPENDS_PCRE} ${DEPENDS_LIBDL} \
				${DEPENDS_LIBINTL} ${DEPENDS_LIBRESOLV} \
				${DEPENDS_THREADS}"
DEPENDS_${PN}-libgthread-2.0 += "libc ${DEPENDS_THREADS} ${DEPENDS_PCRE} \
				libglib-2.0"
DEPENDS_${PN}-libgobject-2.0 += "libc libgcc libffi libgthread-2.0 \
				${DEPENDS_THREADS} ${DEPENDS_PCRE} \
				libglib-2.0"
DEPENDS_${PN}-libgmodule-2.0 += "libc ${DEPENDS_LIBDL} ${DEPENDS_PCRE} \
				libglib-2.0 ${DEPENDS_THREADS}"
DEPENDS_${PN}-libgio-2.0 += "libc libgcc ${DEPENDS_LIBDL} ${DEPENDS_LIBRESOLV} \
				libz libffi libglib-2.0 libgmodule-2.0 \
				libgobject-2.0 libgthread-2.0 ${DEPENDS_PCRE} \
				${DEPENDS_THREADS}"

FILES_${PN}-libgio-2.0-dev += "${libdir}/pkgconfig/gio-*-2.0.pc \
				${datadir}/gettext/its"
FILES_${PN}-libgmodule-2.0-dev += "${libdir}/pkgconfig/gmodule-*-2.0.pc"
FILES_${PN} += "${libdir}/charset.alias"

#To be removed in next base master release!
PROVIDES_${PN}-libglib-2.0 += "libglib"
PROVIDES_${PN}-libglib-2.0 += "glib-libglib"
PROVIDES_${PN}-libglib-2.0-dev += "libglib-dev"
PROVIDES_${PN}-libglib-2.0-dev += "glib-libglib-dev"
PROVIDES_${PN}-libglib-2.0[qa] += "allow-missing-soname:libglib"
PROVIDES_${PN}-libgobject-2.0 += "libgobject"
PROVIDES_${PN}-libgobject-2.0 += "glib-libgobject"
PROVIDES_${PN}-libgobject-2.0-dev += "libgobject-dev"
PROVIDES_${PN}-libgobject-2.0-dev += "glib-libgobject-dev"
PROVIDES_${PN}-libgobject-2.0[qa] += "allow-missing-soname:libgobject"
PROVIDES_${PN}-libgmodule-2.0 += "libgmodule"
PROVIDES_${PN}-libgmodule-2.0 += "glib-libgmodule"
PROVIDES_${PN}-libgmodule-2.0-dev += "libgmodule-dev"
PROVIDES_${PN}-libgmodule-2.0-dev += "glib-libgmodule-dev"
PROVIDES_${PN}-libgmodule-2.0[qa] += "allow-missing-soname:libgmodule"
PROVIDES_${PN}-libgthread-2.0 += "libgthread"
PROVIDES_${PN}-libgthread-2.0 += "glib-libgthread"
PROVIDES_${PN}-libgthread-2.0-dev += "libgthread-dev"
PROVIDES_${PN}-libgthread-2.0-dev += "glib-libgthread-dev"
PROVIDES_${PN}-libgthread-2.0[qa] += "allow-missing-soname:libgthread"
PROVIDES_${PN}-libgio-2.0 += "libgio"
PROVIDES_${PN}-libgio-2.0 += "glib-libgio"
PROVIDES_${PN}-libgio-2.0-dev += "libgio-dev"
PROVIDES_${PN}-libgio-2.0-dev += "glib-libgio-dev"
PROVIDES_${PN}-libgio-2.0[qa] += "allow-missing-soname:libgio"
