# -*- mode:python; -*-
require glib-common.inc

RECIPE_TYPES = "native"

PN = "glib"

# Set these vars so we don't have to use pkg-config, thus breaking the
# glib <-> pkg-config circular dependency.
EXTRA_OECONF += 'ZLIB_CFLAGS=""'
EXTRA_OECONF += 'ZLIB_LIBS="-lz"'
EXTRA_OECONF += 'LIBFFI_CFLAGS="-I`ls -d ${STAGE_DIR}/${HOST_TYPE}${libdir}/libffi-*/include`"'
EXTRA_OECONF += 'LIBFFI_LIBS="-lffi"'
EXTRA_OECONF += 'PCRE_CFLAGS=""'
EXTRA_OECONF += 'PCRE_LIBS=""'
EXTRA_OECONF += 'DBUS1_CFLAGS=""'
EXTRA_OECONF += 'DBUS1_LIBS=""'

# Minimize external dependencies for native glib
EXTRA_OECONF += "--with-libiconv=no"
EXTRA_OECONF += "--with-pcre=internal"
EXTRA_OECONF += "--disable-fam"

do_patch[postfuncs] += "do_patch_glib_gettextize_native"
do_patch_glib_gettextize_native () {
	sed -i -e 's/^\(gettext_dir\)=/\1=\$sysroot/' \
		${S}/glib-gettextize.in
}
