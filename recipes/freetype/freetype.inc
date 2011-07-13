DESCRIPTION = "Freetype font rendering library"
SECTION = "libs"
LICENSE = "freetype GPLv2"
PR = "r0"
DEPENDS = "zlib"

require conf/fetch/sourceforge.conf
SRC_URI = "\
  ${SOURCEFORGE_MIRROR}/freetype/freetype-${PV}.tar.bz2 \
  file://no-hardcode.patch \
  file://fix-configure.patch \
  file://libtool-tag.patch \
"
S = "${SRCDIR}/freetype-${PV}"

inherit autotools pkgconfig binconfig

EXTRA_OEMAKE += "'LIBTOOL=${LIBTOOL}'"

do_compile_prepend() {
	${BUILD_CC} -o objs/apinames src/tools/apinames.c
}

BBCLASSEXTEND = "native"

FILES_${PN} = "${libdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"
