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
