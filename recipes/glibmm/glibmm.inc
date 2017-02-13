DESCRIPTION = "Official C++ interface for Glib"

require conf/fetch/gnome.conf

SRC_URI_SUBDIR = "${@'.'.join(d.getVar('PV', True).split('.')[:2])}"
SRC_URI="${GNOME_MIRROR}/glibmm/${SRC_URI_SUBDIR}/glibmm-${PV}.tar.xz"

inherit autotools-autoreconf c++ pkgconfig
inherit auto-package-libs
AUTO_PACKAGE_LIBS = "giomm-2.4 glibmm-2.4 glibmm_generate_extra_defs-2.4"
COMPATIBLE_HOST_ARCHS = ".*linux"
LIBRARY_VERSION = "1"

AUTO_PACKAGE_LIBS_RDEPENDS = "\
libc libdl libffi libgcc-s libglib-2.0 libgmodule-2.0 libgobject-2.0 \
libm libpcre libpthread libsigc-2.0 libstdc++ \
"

AUTO_PACKAGE_LIBS_DEPENDS = "${AUTO_PACKAGE_LIBS_RDEPENDS}"
DEPENDS_${PN}-libgiomm-2.4  += "libblkid libglibmm-2.4 libmount libresolv librt libuuid libz libgio-2.0"
RDEPENDS_${PN}-libgiomm-2.4 += "libblkid libglibmm-2.4 libmount libresolv librt libuuid libz libgio-2.0"

DEPENDS += "\
native:perl native:util/mm-common-prepare \
mm-common-dev \
libstdc++ libsigc++ \
libglib-2.0 libgobject-2.0 libgmodule-2.0 \
libgthread-2.0 	libgio-2.0 \
"

FILES_${PN}-doc += "${datadir}/devhelp"
FILES_${PN}-dev += "${libdir}/glibmm-2.4/proc"
