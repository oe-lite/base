DESCRIPTION = "tslib is a plugin-based flexible touchscreen access library."
HOMEPAGE = "http://tslib.berlios.de/"
AUTHOR = "Russell King w/ plugins by Chris Larson et. al."
LICENSE = "LGPLv2"

inherit c++ autotools-autoreconf pkgconfig library

SRC_URI = "http://download.berlios.de/${PN}/${P}.tar.bz2"

SRC_URI_EXTRA = "file://ts.conf file://tslib.sh"
SRC_URI += "${SRC_URI_EXTRA}"

DEPENDS += "libdl"

EXTRA_OECONF += "--enable-shared ac_cv_func_malloc_0_nonnull=yes"

do_install[postfuncs] += "do_install_extra"
do_install_extra () {
	install -d ${D}${sysconfdir}/profile.d/
	install -m 0755 ${SRCDIR}/tslib.sh ${D}${sysconfdir}/profile.d/
	install -m 0644 ${SRCDIR}/ts.conf ${D}${sysconfdir}/ts.conf
}

PACKAGES =+ "${PN}-conf ${PN}-tests ${PN}-calibrate"

FILES_${PN}-dbg += "${libdir}/ts/.debug*"
FILES_${PN}-conf = "${sysconfdir}/ts.conf ${sysconfdir}/profile.d/tslib.sh ${datadir}/tslib"
FILES_${PN} = "${libdir}/*${SOLIBS} ${libdir}/ts/*.so"
FILES_${PN}-dev += "${libdir}/ts/*.la ${libdir}/ts/*.a"
FILES_${PN}-calibrate = "${bindir}/ts_calibrate"
FILES_${PN}-tests = "${bindir}/ts_harvest ${bindir}/ts_print ${bindir}/ts_print_raw ${bindir}/ts_test"

LIBRARY_NAME = "libts"

RDEPENDS_${PN} = "libdl ${PN}-conf"
RDEPENDS_${PN}-tests = "${PN}"
RDEPENDS_${PN}-calibrate = "${PN}"
