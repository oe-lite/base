DESCRIPTION = "Very high-quality data compression program"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf pkgconfig

SRC_URI = "http://www.bzip.org/${PV}/bzip2-${PV}.tar.gz"

inherit auto-package-libs auto-package-utils

AUTO_PACKAGE_LIBS = "bz2"
FILES_${PN}-libbz2-dev = "${includedir}"

AUTO_PACKAGE_UTILS = "bzip2 bzdiff bzgrep bzip2recover bzmore"

FILES_${PN}-bzip2 = "${bindir}/bunzip2 ${bindir}/bzcat"
FILES_${PN}-bzdiff = "${bindir}/bzcmp"
FILES_${PN}-bzgrep = "${bindir}/bzegrep ${bindir}/bzfgrep"
FILES_${PN}-bzmore = "${bindir}/bzless"

FILES_${PN}-bzip2-doc = "${mandir}/man1/bunzip2.1 ${mandir}/man1/bzcat.1"
FILES_${PN}-bzdiff-doc = "${mandir}/man1/bzcmp.1"
FILES_${PN}-bzgrep-doc = "${mandir}/man1/bzegrep.1 ${mandir}/man1/bzfgrep.1"
FILES_${PN}-bzmore-doc = "${mandir}/man1/bzless.1"

RPROVIDES_${PN}-bzip2 = "util/bunzip2 util/bzcat"
RPROVIDES_${PN}-bzdiff = "util/bzcmp"
RPROVIDES_${PN}-bzgrep = "util/bzegrep util/bzfgrep"
RPROVIDES_${PN}-bzmore = "util/bzless"

RDEPENDS_${PN} = "${PN}-bzip2 ${PN}-bzdiff ${PN}-bzgrep ${PN}-bzip2recover ${PN}-bzmore"
RDEPENDS_${PN}-bzip2 = "${PN}-libbz2"
RDEPENDS_${PN}-bzdiff = "${PN}-libbz2"
RDEPENDS_${PN}-bzgrep = "${PN}-libbz2"
RDEPENDS_${PN}-bzip2recover = "${PN}-libbz2"
RDEPENDS_${PN}-bzmore = "${PN}-libbz2"

do_autoreconf[prefuncs] += "do_autoreconf_prep"
do_autoreconf_prep() {
	ln -sf LICENSE COPYING
	ln -sf CHANGES NEWS
	touch AUTHORS
	touch ChangeLog
}
