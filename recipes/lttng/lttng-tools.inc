# -*- mode:python; -*-
DESCRIPTION = "LTTng Trace Control"
LICENSE = "GPLv2.1+"

RECIPE_TYPES = "machine"

DEPENDS += "libc libdl librt libpthread libuuid libpopt libuuid \
	${DEPENDS_LTTNG} native:bison"
DEPENDS_LTTNG ?= "liburcu-2 liblttng-ust-0 liblttng-ust-ctl-2 \
	liblttng-ust-fork-0 liblttng-ust-libc-wrapper-0"

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
FILES_${PN}-liblttng-ctl-dev = "${includedir}/lttng/lttng.h"
DEPENDS_${PN}-liblttng-ctl = "libc librt libpthread libuuid libpopt \
	liburcu-common liburcu"
RDEPENDS_${PN}-liblttng-ctl = "libc librt libpthread libuuid libpopt \
	liburcu-common liburcu"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "lttng lttng-consumerd lttng-sessiond lttng-relayd"
AUTO_PACKAGE_UTILS_DEPENDS += "libc libuuid liburcu liburcu-common"
AUTO_PACKAGE_UTILS_RDEPENDS += "liburcu libuuid liburcu-common"
DEPENDS_${PN}-lttng = "librt libpopt liblttng-ctl"
RDEPENDS_${PN}-lttng = "librt libpopt liblttng-ctl"
DEPENDS_${PN}-lttng-consumerd = "librt liblttng-ust-ctl liburcu-bp \
	liburcu-cds liblttng-ctl"
RDEPENDS_${PN}-lttng-consumerd = "librt liblttng-ust-ctl liburcu-bp \
	liburcu-cds liblttng-ctl"
DEPENDS_${PN}-lttng-sessiond = "libdl librt liblttng-ctl liblttng-ust-ctl \
	liburcu-bp liburcu-cds"
RDEPENDS_${PN}-lttng-sessiond = "libdl librt liblttng-ctl liblttng-ust-ctl \
	liburcu-bp liburcu-cds"
DEPENDS_${PN}-lttng-relayd = "librt libpopt liblttng-ctl"
RDEPENDS_${PN}-lttng-relayd = "liblttng-ctl"
DEPENDS_${PN} += "libc libdl librt libpthread libuuid libpopt \
	liblttng-ctl liblttng-ust liblttng-ust-ctl \
	liburcu liburcu-bp liburcu-cds liburcu-common"
RDEPENDS_${PN} += "libc libdl librt libpthread libuuid libpopt \
	liblttng-ctl liblttng-ust liblttng-ust-ctl \
	liburcu liburcu-bp liburcu-cds liburcu-common"
