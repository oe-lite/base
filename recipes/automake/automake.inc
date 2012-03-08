SUMMARY = "A GNU tool for automatically generating Makefiles."
DESCRIPTION = "Automake is a tool for automatically generating Makefile.in \
	files compliant with the GNU Coding Standards. \
	Automake requires the use of Autoconf."
LICENSE = "GPLv2"
HOMEPAGE = "http://www.gnu.org/software/automake/"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/automake/automake-${PV}.tar.gz "

inherit autotools

FILES_${PN} += "${datadir}/automake* ${datadir}/aclocal*"
