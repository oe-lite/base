# -*- mode:python; -*-
DESCRIPTION = "A mature, widely used set of C/C++ and Java libraries providing Unicode and Globalization support for software applications"
HOMEPAGE = "http://icu-project.org/"
LICENSE = "ICU"

RECIPE_TYPES = "machine native sdk"

inherit c++ autotools pkgconfig binconfig

DEPENDS = "libstdc++ libm ${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread libdl"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

CROSS_DEPENDS = "native:icu-src"
CROSS_DEPENDS:native = ""
DEPENDS += "${CROSS_DEPENDS}"

SRC_URI = "http://download.icu-project.org/files/icu4c/${PV}/icu4c-${@'${PV}'.replace('.','_')}-src.tgz"

S = "${SRCDIR}/icu/source"

EXTRA_OECONF = "--enable-static"

CROSS_EXTRA_OECONF = "--with-cross-build=${STAGE_DIR}/native${stage_prefix}/src/icu"
CROSS_EXTRA_OECONF:native = ""
EXTRA_OECONF += "${CROSS_EXTRA_OECONF}"

# FIXME: improve binconfig.oeclass to rewrite *-config (icu-config) in
# install/ dir (install fixup), stripping out stage sysroot prefix,
# and perhaps even fixing up again after unpacking to stage dir (stage
# fixup)

# Package up the entire native build tree for use when cross-compiling, *sigh*
do_install[postfuncs] += "${DO_INSTALL_SRC}"
DO_INSTALL_SRC = ""
DO_INSTALL_SRC:native = "do_install_src"
do_install_src () {
    mkdir -p ${D}${prefix}/src/icu
    cp -r ${S}/. ${D}${prefix}/src/icu
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-dev ${PN} ${PN}-locale"

NATIVE_PACKAGES = ""
NATIVE_PACKAGES:native = "${PN}-src"
PACKAGES += "${NATIVE_PACKAGES}"

FILES_${PN}-doc += "${datadir}/icu/${PV}/license.html"
FILES_${PN}-dev += "${bindir}/icu-config ${libdir}/icu ${datadir}/icu/ \
    ${datadir}/icu/${PV} ${libdir}/icu"

FILES_${PN}-src = "${prefix}/src/icu"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "icudata icuuc icui18n icule iculx icutu icuio icutest"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"

# FIXME: it should be possible to make icu-dev build independent of icu
# and then remove the DEPENDS_icu-dev on icu...
DEPENDS_${PN}-dev = ""

RDEPENDS_${PN} = "libicudata libicui18n libicutu libicuuc \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicui18n = "libicuuc libicudata \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicuio = "libicuuc libicudata libicui18n \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicule = "libicuuc libicudata \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libiculx = "libicuuc libicudata libicule \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicutest = "libicutu libicui18n libicuuc libicudata \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicutu = "libicui18n libicuuc libicudata \
	libc libdl libgcc libm libpthread libstdc++"

DEPENDS_${PN}-libicuuc = "libicudata \
	libc libdl libgcc libm libpthread libstdc++"
