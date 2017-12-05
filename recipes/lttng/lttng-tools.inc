# -*- mode:python; -*-
DESCRIPTION = "LTTng Trace Control"
LICENSE = "GPLv2.1+"

RECIPE_TYPES = "machine"

DEPENDS += "libc libdl librt libpthread libuuid libpopt libuuid \
	${DEPENDS_LTTNG} native:bison"
DEPENDS_LTTNG ?= "liburcu liblttng-ust liblttng-ust-ctl \
	liblttng-ust-fork liblttng-ust-libc-wrapper"

inherit autotools-autoreconf make pkgconfig

SRC_URI = "http://lttng.org/files/lttng-tools/lttng-tools-${PV}.tar.bz2"

EXTRA_OECONF += "CFLAGS=-I${WORKDIR}/build/include/"

do_install[postfuncs] += "do_install_fixup_consumerd"
do_install_fixup_consumerd() {
	cp -aR ${D}${libdir}/lttng/libexec/* ${D}${bindir}
	rm -rf ${D}${libdir}/lttng
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "lttng-ctl"
FILES_${PN}-liblttng-ctl = "${datadir}/xml/lttng"
FILES_${PN}-liblttng-ctl-dev = "${includedir}/lttng/lttng.h"
DEPENDS_${PN}-liblttng-ctl = "libc librt libpthread libuuid libpopt \
	liburcu-common liburcu"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "lttng lttng-consumerd lttng-sessiond lttng-relayd"
AUTO_PACKAGE_UTILS_DEPENDS += "libc librt libuuid liburcu liburcu-cds"
AUTO_PACKAGE_UTILS_RDEPENDS += "${AUTO_PACKAGE_UTILS_DEPENDS}"
DEPENDS_${PN}-lttng = "liblttng-ctl libpopt"
DEPENDS_${PN}-lttng-consumerd = "liblttng-ust-ctl liburcu-bp"
DEPENDS_${PN}-lttng-sessiond = "liblttng-ctl liblttng-ust-ctl liburcu-bp"
DEPENDS_${PN}-lttng-relayd = "liblttng-ctl"
RDEPENDS_${PN}-lttng = "${DEPENDS_${PN}-lttng}"
RDEPENDS_${PN}-lttng-consumerd = "${DEPENDS_${PN}-lttng-consumerd}"
RDEPENDS_${PN}-lttng-sessiond = "${DEPENDS_${PN}-lttng-sessiond}"
RDEPENDS_${PN}-lttng-relayd = "${DEPENDS_${PN}-lttng-relayd}"
