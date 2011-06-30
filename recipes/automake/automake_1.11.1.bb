require automake.inc
LICENSE="GPLv2"

RECIPE_TYPES = "machine sdk native"

DEPENDS = "native:autoconf"
RDEPENDS_${PN} += "autoconf"

do_install () {
	oe_runmake 'DESTDIR=${D}' install
	install -d ${D}${datadir}
}
