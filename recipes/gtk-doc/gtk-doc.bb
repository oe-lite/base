SRC_URI = "file://gtk-doc.m4"
LICENSE = "LGPL"
PR = "r3"

RECIPE_TYPES = "native"

do_install() {
	install -d ${D}/${datadir}/aclocal
	install -m 0644 ${SRCDIR}/gtk-doc.m4 ${D}/${datadir}/aclocal
}

PACKAGES = "${PN}"
FILES_${PN} = "${datadir}/aclocal/gtk-doc.m4"
