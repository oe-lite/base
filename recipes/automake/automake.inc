SUMMARY = "A GNU tool for automatically generating Makefiles."
DESCRIPTION = "Automake is a tool for automatically generating Makefile.in \
	files compliant with the GNU Coding Standards. \
	Automake requires the use of Autoconf."
LICENSE = "GPLv2"
HOMEPAGE = "http://www.gnu.org/software/automake/"

RECIPE_TYPES = "machine sdk native"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/automake/automake-${PV}.tar.gz "

inherit autotools

DEPENDS = "native:autoconf"
RDEPENDS_${PN} += "autoconf"

do_install () {
	oe_runmake 'DESTDIR=${D}' install
	install -d ${D}${datadir}
}

FILES_${PN} += "${datadir}/automake* ${datadir}/aclocal*"
