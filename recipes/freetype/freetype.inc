# -*- mode:python; -*-
DESCRIPTION = "Freetype font rendering library"
LICENSE = "freetype GPLv2"

RECIPE_TYPES = "machine native"

inherit library autotools pkgconfig binconfig

DEPENDS = "libz libpng"

require conf/fetch/savannah.conf
SRC_URI = "${SAVANNAH_MIRROR}/freetype/freetype-${PV}.tar.bz2"

RECIPE_FLAGS += "freetype_without_png"
DEFAULT_USE_freetype_without_png = " "

EXTRA_OECONF:>USE_freetype_without_png += " --without-png"

# Following required for configure to accept libpng
export LIBPNG_CFLAGS = " "
export LIBPNG_DFLAGS = " "

do_compile[postfuncs] += "do_compile_apinames"
do_compile_apinames() {
	${BUILD_CC} -o objs/apinames src/tools/apinames.c
}

FILES_${PN} = "${sharedlibdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"

DEPENDS_${PN} += "libc libz libpng"
RDEPENDS_${PN} += "libc libz libpng"

RECIPE_FLAGS += "freetype_bzip2"
DEPENDS:>USE_freetype_bzip2 = " libbz2"
EXTRA_OECONF += "${EXTRA_OECONF_BZIP2}"
EXTRA_OECONF_BZIP2 = "--without-bzip2"
EXTRA_OECONF_BZIP2:USE_freetype_bzip2 = "--with-bzip2"
DEPENDS_${PN}:>USE_freetype_bzip2 = " libbz2"
RDEPENDS_${PN}:>USE_freetype_bzip2 = " libbz2"
