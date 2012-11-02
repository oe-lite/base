# -*- mode:python; -*-
DESCRIPTION = "LTTng Trace Control"
LICENSE = "GPLv2.1+"

RECIPE_TYPES = "machine"

inherit autotools-autoreconf make pkgconfig

SRC_URI = "http://lttng.org/files/lttng-tools/lttng-tools-${PV}.tar.bz2"

LIBRARY_DEPENDS = "libpopt liburcu libpthread librt libuuid libdl"

LIBRARY_DEPENDS += "lttng-ust${DEPENDS_LTTNG_UST_VERSION}"
DEPENDS_LTTNG_UST_VERSION ?= ""

EXTRA_OECONF += "CFLAGS=-I${WORKDIR}/build/include/"

# Recipe build dependencies
DEPENDS =+ "${LIBRARY_DEPENDS} lttng-ust-dev${DEPENDS_LTTNG_UST_VERSION}"

# Package dependencies
DEPENDS_${PN} += "${LIBRARY_DEPENDS}"
RDEPENDS_${PN} += "${LIBRARY_DEPENDS}"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "lttngctl lttngkconsumerd"
FILES_${PN}-liblttngctl-dev = "${includedir}/lttng/lttng.h"
FILES_${PN}-liblttngkconsumerd-dev = "${includedir}/lttng/lttng-kconsumerd.h"
DEPENDS_${PN}-liblttngctl = "libpopt libpthread libc"
DEPENDS_${PN}-liblttngkconsumerd = "libpopt libpthread libc"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "lttng ltt-kconsumerd ltt-sessiond"
RDEPENDS_${PN}-lttng = "liblttngctl libpopt libpthread libc"
RDEPENDS_${PN}-ltt-kconsumerd = "liblttngkconsumerd libpopt libpthread libc"
RDEPENDS_${PN}-ltt-sessiond = "liblttngctl libpopt libpthread librt libc"
RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
