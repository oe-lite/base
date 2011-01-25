require ${BPN}.inc

SRC_URI += "file://glibconfig-sysdefs.h"
SRC_URI += "file://configure-libtool.patch"
SRC_URI += "file://g_once_init_enter.patch"
SRC_URI += "file://gatomic-proper-pointer-get-cast.patch"
SRC_URI += "file://gio.patch"
SRC_URI += "file://60_wait-longer-for-threads-to-die.patch"
SRC_URI += "file://glib-mkenums-interpreter.patch"
#SRC_URI += "file://disable-ipv6.patch"

#SRC_URI_append_arm = " file://atomic-thumb.patch"
#SRC_URI_append_armv6 = " file://gatomic_armv6.patch"
#SRC_URI_append_armv7a = " file://gatomic_armv6.patch"

do_configure_prepend () {
	install -m 0644 ${SRCDIR}/glibconfig-sysdefs.h .
}
