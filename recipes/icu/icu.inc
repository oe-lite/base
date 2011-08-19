DESCRIPTION = "A mature, widely used set of C/C++ and Java libraries providing Unicode and Globalization support for software applications"
HOMEPAGE = "http://icu-project.org/"
LICENSE = "ICU"

BBCLASSEXTEND = "native sdk"

inherit c++ autotools pkgconfig binconfig

CROSS_DEPENDS = "icu-native-src"
CROSS_DEPENDS_recipe-native = ""
DEPENDS += "${CROSS_DEPENDS}"

SRC_URI = "http://download.icu-project.org/files/icu4c/${PV}/icu4c-${@'${PV}'.replace('.','_')}-src.tgz"

S = "${SRCDIR}/icu/source"

EXTRA_OECONF = "--enable-static"

CROSS_EXTRA_OECONF = "--with-cross-build=${STAGE_DIR}/native${stage_prefix}/src/icu"
CROSS_EXTRA_OECONF_recipe-native = ""
EXTRA_OECONF += "${CROSS_EXTRA_OECONF}"

# FIXME: improve binconfig.oeclass to rewrite *-config (icu-config) in
# install/ dir (install fixup), stripping out stage sysroot prefix,
# and perhaps even fixing up again after unpacking to stage dir (stage
# fixup)

# Package up the entire native build tree for use when cross-compiling, *sigh*
do_install_append_recipe-native () {
    mkdir -p ${D}${prefix}/src/icu
    cp -r ${S}/. ${D}${prefix}/src/icu
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-dev ${PN} ${PN}-locale"

NATIVE_PACKAGES = ""
NATIVE_PACKAGES_recipe-native = "${PN}-src"
PACKAGES += "${NATIVE_PACKAGES}"
PROVIDES_${PN}-src = "${PN}-src"

FILES_${PN}-doc += "${datadir}/icu/${PV}/license.html"
FILES_${PN}-dev += "${bindir}/icu-config ${libdir}/icu ${datadir}/icu/ \
    ${datadir}/icu/${PV} ${libdir}/icu"

FILES_${PN}-src = "${prefix}/src/icu"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "icudata icuuc icui18n icule iculx icutu icuio icutest"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "icu-dev"

# FIXME: it should be possible to make icu-dev build independent of icu
# and then remove the DEPENDS_icu-dev on icu...
DEPENDS_${PN}-dev = ""
