require automake.inc
LICENSE="GPLv2"

BBCLASSEXTEND = "native"

DEPENDS = "autoconf-native"
RDEPENDS_${PN} += "autoconf${RE}"

do_install () {
	oe_runmake 'DESTDIR=${D}' install
	install -d ${D}${datadir}
}
