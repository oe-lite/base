DESCRIPTION = "Make system for boost (native)"
HOMEPAGE = "http://www.boost.org/"
LICENSE = "Boost Software License"

RECIPE_TYPES = "native"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/boost/boost-jam-${PV}.tgz"

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
