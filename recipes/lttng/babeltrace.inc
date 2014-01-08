# -*- mode:python; -*-
SUMMARY = "Babeltrace - Trace Format Babel Tower"
DESCRIPTION = "Babeltrace provides trace read and write libraries in host side,\
	 as well as a trace converter, which used to convert LTTng 2.0 traces \
	 into human-readable log."
HOMEPAGE = "http://www.efficios.com/babeltrace/"
LICENSE = "MIT & GPLv2"

RECIPE_TYPES = "machine sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit autotools-autoreconf pkgconfig make-vpath auto-package-libs

SRC_URI = "http://www.efficios.com/files/babeltrace/babeltrace-${PV}.tar.bz2"

DEPENDS += "libpopt libgmodule-2.0 ${DEPENDS_LIBUUID} ${DEPENDS_LIBC}"
DEPENDS_LIBC = "librt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS_LIBUUID = "libuuid"
DEPENDS_LIBUUID:HOST_LIBC_mingw = ""

AUTO_PACKAGE_LIBS = "babeltrace babeltrace-ctf-metadata babeltrace-ctf-text \
		babeltrace-ctf babeltrace-dummy"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc libdl libglib-2.0 libgmodule-2.0 libpcre \
				libpopt libpthread"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libdl libglib-2.0 libgmodule-2.0 libpcre \
				libpopt libpthread"


DEPENDS_${PN} += "libbabeltrace libbabeltrace-ctf \
		libbabeltrace-ctf-metadata libbabeltrace-ctf-text \
		libbabeltrace-dummy libc libdl libglib-2.0 libgmodule-2.0 \
		libpcre libpopt libpthread ${DEPENDS_LIBUUID}"
RDEPENDS_${PN} += "libgmodule-2.0 libpopt ${DEPENDS_LIBUUID} libpcre libpthread libc \
		libglib-2.0 libdl ${DEPENDS_LIBC} libbabeltrace libbabeltrace-ctf \
		libbabeltrace-ctf-metadata libbabeltrace-ctf-text \
		libbabeltrace-dummy"
DEPENDS_${PN}-libbabeltrace-ctf-metadata += "libbabeltrace"
RDEPENDS_${PN}-libbabeltrace-ctf-metadata += "libbabeltrace"
DEPENDS_${PN}-libbabeltrace-ctf += "libbabeltrace ${DEPENDS_LIBUUID}"
RDEPENDS_${PN}-libbabeltrace-ctf += "libbabeltrace ${DEPENDS_LIBUUID}"
DEPENDS_${PN}-libbabeltrace-ctf-text += "libbabeltrace libbabeltrace-ctf ${DEPENDS_LIBUUID}"
RDEPENDS_${PN}-libbabeltrace-ctf-text += "libbabeltrace libbabeltrace-ctf ${DEPENDS_LIBUUID}"
DEPENDS_${PN}-libbabeltrace-dummy += "libbabeltrace"
RDEPENDS_${PN}-libbabeltrace-dummy += "libbabeltrace"
