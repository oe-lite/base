DESCRIPTION = "Freetype font rendering library"
LICENSE = "freetype GPLv2"

RECIPE_TYPES = "machine native"

inherit library autotools pkgconfig binconfig

DEPENDS = "libz"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/freetype/freetype-${PV}.tar.bz2"

SRC_URI += "file://no-hardcode.patch"

EXTRA_OEMAKE += "'LIBTOOL=${LIBTOOL}'"

do_compile[postfuncs] += "do_compile_apinames"
do_compile_apinames() {
	${BUILD_CC} -o objs/apinames src/tools/apinames.c
}

FILES_${PN} = "${libdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"
