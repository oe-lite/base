require ${BPN}.inc

SRC_URI += "file://glibconfig-sysdefs.h"
SRC_URI += "file://g_once_init_enter.patch"
SRC_URI += "file://gatomic-proper-pointer-get-cast.patch"
SRC_URI += "file://60_wait-longer-for-threads-to-die.patch"
SRC_URI += "file://glib-mkenums-interpreter.patch"
SRC_URI += "file://libglib2-fix-compilation-with-no-builtin-atomic.patch"
SRC_URI += "file://configure-ipv6.patch"

do_configure_prepend () {
    install -m 0644 ${SRCDIR}/glibconfig-sysdefs.h .
}
