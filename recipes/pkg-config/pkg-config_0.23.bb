require ${BPN}.inc

SRC_URI_append = "\
	file://autofoo.patch;patch=1 \
	file://sysrootfix.patch;patch=1 \
	file://glibconfig-sysdefs.h \
"

do_configure_prepend () {
	install -m 0644 ${SRCDIR}/glibconfig-sysdefs.h glib-1.2.*/
}
