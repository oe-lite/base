# The Boost web site provides free peer-reviewed portable
# C++ source libraries. The emphasis is on libraries which
# work well with the C++ Standard Library. The libraries are
# intended to be widely useful, and are in regular use by
# thousands of programmers across a broad spectrum of applications.
DESCRIPTION = "Make system for boost (native)"
HOMEPAGE = "http://www.boost.org/"
SECTION = "devel"
PRIORITY = "optional"
LICENSE = "Boost Software License"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/boost/boost-jam-${PV}.tgz"

inherit native

do_compile() {
	set -ex
	rm -rf bin.*
	./build.sh gcc
}

do_install() {
	set -ex
	install -d ${D}${stage_bindir}
	install -c -m 755 bin.*/bjam ${D}${stage_bindir}/
}
