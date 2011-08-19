# -*- mode:python; -*-
DESCRIPTION = "Jim Clarkes XML parser library."
HOMEPAGE = "http://expat.sf.net/"
LICENSE = "MIT"

RECIPE_TYPES = "machine native sdk"

inherit autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/expat/expat-${PV}.tar.gz"

export LTCC = "${CC}"

PACKAGES = "${PN}-dbg ${PN} ${PN}-doc ${PN}-locale"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "expat"
FILES_${PN}-libexpat-dev = "\
${base_libdir}/*${SOLIBSDEV} ${base_libdir}/*.a ${base_libdir}/*.la \
${libdir}/lib*${SOLIBSDEV} ${libdir}/*.a ${libdir}/*.la \
${base_libdir}/*.o  ${libdir}/*.o \
${libdir}/pkgconfig \
${includedir} \
${libdir}/*/include \
${datadir}/aclocal ${datadir}/pkgconfig \
${bindir}/*-config \
"

RDEPENDS_${PN} = "libexpat"
