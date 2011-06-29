DESCRIPTION = "tslib is a plugin-based flexible touchscreen access library."
HOMEPAGE = "http://tslib.berlios.de/"
AUTHOR = "Russell King w/ plugins by Chris Larson et. al."
LICENSE = "LGPLv2"

inherit autotools-autoreconf pkgconfig

PACKAGES =+ "${PN}-conf ${PN}-tests ${PN}-calibrate"
DEPENDS += "${HOST_ARCH}/sysroot-libdl ${HOST_ARCH}/sysroot-libstdc++"

SRC_URI = "http://download.berlios.de/${BPN}/${BP}.tar.bz2"
SRC_URI += "file://ts.conf"
SRC_URI += "file://tslib.sh"

EXTRA_OECONF += "--enable-shared ac_cv_func_malloc_0_nonnull=yes"

do_install_append () {
	install -d ${D}${sysconfdir}/profile.d/
	install -m 0755 ${SRCDIR}/tslib.sh ${D}${sysconfdir}/profile.d/
	install -m 0644 ${SRCDIR}/ts.conf ${D}${sysconfdir}/ts.conf
}

RDEPENDS_${PN} = "${HOST_ARCH}/sysroot-libdl ${PN}-conf"
RDEPENDS_${PN}-tests = "${PN}"
RDEPENDS_${PN}-calibrate = "${PN}"
PROVIDES_${PN}-dev	+= "libts"
RPROVIDES_${PN}		+= "libts"

FILES_${PN}-dbg += "${libdir}/ts/.debug*"
FILES_${PN}-conf = "${sysconfdir}/ts.conf ${sysconfdir}/profile.d/tslib.sh ${datadir}/tslib"
FILES_${PN} = "${libdir}/*${SOLIBS} ${libdir}/ts/*.so"
FILES_${PN}-dev += "${libdir}/ts/*.la ${libdir}/ts/*.a"
FILES_${PN}-calibrate = "${bindir}/ts_calibrate"
FILES_${PN}-tests = "${bindir}/ts_harvest ${bindir}/ts_print ${bindir}/ts_print_raw ${bindir}/ts_test"
