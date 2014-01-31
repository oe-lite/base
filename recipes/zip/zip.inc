DESCRIPTION = "Archiver for .zip files"
HOMEPAGE = "http://www.info-zip.org"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit c make auto-package-utils

SRC_URI = "ftp://ftp.info-zip.org/pub/infozip/src/zip${@d.getVar('PV',1).replace('.', '')}.tgz"

EXTRA_OEMAKE = "'CC=${CC}' 'BIND=${CC}' 'AS=${CC} -c' 'CPP=${CPP}' \
		'CFLAGS=-I. -DUNIX ${CFLAGS}' 'INSTALL=install' \
		'BINFLAGS=0755' 'INSTALL_D=install -d'"

do_compile() {
	oe_runmake -f unix/Makefile generic
}

do_install() {
	oe_runmake -f unix/Makefile prefix=${D}${prefix} \
		   BINDIR=${D}${bindir} MANDIR=${D}${mandir}/man1 \
		   install
}

AUTO_PACKAGE_UTILS = "zip zipcloak zipnote zipsplit"
