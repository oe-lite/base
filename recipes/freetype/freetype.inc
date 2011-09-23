DESCRIPTION = "Freetype font rendering library"
LICENSE = "freetype GPLv2"

RECIPE_TYPES = "machine native"

DEPENDS = "zlib"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/freetype/freetype-${PV}.tar.bz2"
#S = "${SRCDIR}/freetype-${PV}"

SRC_URI += "file://no-hardcode.patch"
SRC_URI += "file://fix-configure.patch"
SRC_URI += "file://libtool-tag.patch"

inherit library autotools pkgconfig binconfig

EXTRA_OEMAKE += "'LIBTOOL=${LIBTOOL}'"

do_compile[postfuncs] += "do_compile_apinames"
do_compile_apinames() {
	${BUILD_CC} -o objs/apinames src/tools/apinames.c
}

FILES_${PN} = "${libdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"

PROVIDES_${PN} = "libfreetype"
PROVIDES_${PN}-dev = "libfreetype-dev"
