require gettext.inc

SRC_URI += "\
file://autotools.patch;patch=1 \
file://wchar-uclibc.patch;patch=1 \
file://use_open_properly.patch;patch=1 \
file://gettext-autoconf-lib-link-no-L.patch;patch=1 \
file://m4_copy.patch;patch=1 \
"

SRC_URI_append_linux-uclibc = " file://gettext-error_print_progname.patch;patch=1"
SRC_URI_append_linux-uclibceabi = " file://gettext-error_print_progname.patch;patch=1"
