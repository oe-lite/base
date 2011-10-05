# -*- mode:python; -*-
DESCRIPTION = "Freetype font rendering library"
LICENSE = "freetype GPLv2"

RECIPE_TYPES = "machine native"

inherit library autotools pkgconfig binconfig

DEPENDS = "libz"

SRC_URI = "http://download.savannah.gnu.org/releases/freetype/freetype-${PV}.tar.bz2"

SRC_URI += "file://no-hardcode.patch"

EXTRA_OEMAKE += "'LIBTOOL=${LIBTOOL}'"

do_compile[postfuncs] += "do_compile_apinames"
do_compile_apinames() {
	${BUILD_CC} -o objs/apinames src/tools/apinames.c
}

FILES_${PN} = "${libdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"
