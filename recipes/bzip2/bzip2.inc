DESCRIPTION = "Very high-quality data compression program"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf make-vpath pkgconfig

SRC_URI = "http://www.bzip.org/${PV}/bzip2-${PV}.tar.gz"

inherit auto-package-libs auto-package-utils

AUTO_PACKAGE_LIBS = "bz2"
FILES_${PN}-libbz2-dev = "${includedir} ${libdir}/pkgconfig/bzip2.pc"

AUTO_PACKAGE_UTILS = "bzip2 bzdiff bzgrep bzip2recover bzmore"

AUTO_PACKAGE_UTILS_SYMLINKS_bzip2 = "bunzip2 bzcat"
AUTO_PACKAGE_UTILS_SYMLINKS_bzdiff = "bzcmp"
AUTO_PACKAGE_UTILS_SYMLINKS_bzgrep = "bzegrep bzfgrep"
AUTO_PACKAGE_UTILS_SYMLINKS_bzmore = "bzless"

AUTO_PACKAGE_UTILS_RDEPENDS = "libbz2"
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PACKAGES}"

do_autoreconf[prefuncs] += "do_autoreconf_prep"
do_autoreconf_prep() {
	ln -sf LICENSE COPYING
	ln -sf CHANGES NEWS
	touch AUTHORS
	touch ChangeLog
}
