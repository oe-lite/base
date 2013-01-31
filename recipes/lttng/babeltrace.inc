# -*- mode:python; -*-
SUMMARY = "Babeltrace - Trace Format Babel Tower"
DESCRIPTION = "Babeltrace provides trace read and write libraries in host side, as well as a trace converter, which used to convert LTTng 2.0 traces into human-readable log."
HOMEPAGE = "http://www.efficios.com/babeltrace/"
LICENSE = "MIT & GPLv2"

RECIPE_TYPES = "machine sdk"

inherit autotools-autoreconf

SRC_URI = "http://www.efficios.com/files/babeltrace/babeltrace-0.8.tar.bz2"

DEPENDS += "libuuid libpopt libgmodule librt"
RDEPENDS_${PN} += "libgmodule libpopt libuuid libpcre libpthread libc libglib libdl librt"

PACKAGES = "${PN}-dbg ${PN}-doc ${PN} ${PN}-dev ${PN}-locale"
FILES_${PN} += "${libdir}/*.so"
