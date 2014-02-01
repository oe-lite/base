# -*- mode:python; -*-
SUMMARY = "Babeltrace - Trace Format Babel Tower"
DESCRIPTION = "Babeltrace provides trace read and write libraries in host side, as well as a trace converter, which used to convert LTTng 2.0 traces into human-readable log."
HOMEPAGE = "http://www.efficios.com/babeltrace/"
LICENSE = "MIT & GPLv2"

RECIPE_TYPES = "machine sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit autotools-autoreconf pkgconfig make-vpath

SRC_URI = "http://www.efficios.com/files/babeltrace/babeltrace-${PV}.tar.bz2"

DEPENDS += "libpopt libgmodule ${DEPENDS_LIBC}"
DEPENDS_LIBC = "librt libuuid"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
RDEPENDS_${PN} += "libgmodule libpopt libuuid libpcre libpthread libc libglib libdl ${DEPENDS_LIBC}"

PACKAGES = "${PN}-dbg ${PN}-doc ${PN} ${PN}-dev ${PN}-locale"
FILES_${PN} += "${libdir}/*.so"
