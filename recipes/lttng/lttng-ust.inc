# -*- mode:python; -*-
SUMMARY = "Linux Trace Toolkit Userspace Tracer 2.0"
DESCRIPTION = "The LTTng UST 2.0 package contains the userspace tracer library to trace userspace codes."
HOMEPAGE = "http://lttng.org/lttng2.0"

inherit c++ autotools-autoreconf auto-package-libs

DEPENDS_LIBURCU ?= "liburcu-cds liburcu-bp"
DEPENDS = "${DEPENDS_LIBURCU} libuuid librt libdl"
SRC_URI = "http://lttng.org/files/lttng-ust/lttng-ust-${PV}.tar.bz2"

PACKAGES += "${PN}-demos"

FILES_${PN}-demos = "/tmp/"

DEPENDS_${PN} += "${DEPENDS_LIBURCU}"
RDEPENDS_${PN} += "${DEPENDS_LIBURCU}"

AUTO_PACKAGE_LIBS += "lttng-ust-ctl lttng-ust-cyg-profile-fast \
	lttng-ust-cyg-profile lttng-ust-fork lttng-ust-libc-wrapper \
	lttng-ust lttng-ust-tracepoint"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc libpthread ${PN}-dev ${DEPENDS_LIBURCU}"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libpthread ${DEPENDS_LIBURCU}"

DEPENDS_${PN}-liblttng-ust-ctl += "librt"
RDEPENDS_${PN}-liblttng-ust-ctl += "librt"

DEPENDS_${PN}-liblttng-ust-cyg-profile-fast += "libdl liblttng-ust librt"
RDEPENDS_${PN}-liblttng-ust-cyg-profile-fast += "libdl liblttng-ust librt"

DEPENDS_${PN}-liblttng-ust-cyg-profile += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"
RDEPENDS_${PN}-liblttng-ust-cyg-profile += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"

DEPENDS_${PN}-liblttng-ust-fork += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"
RDEPENDS_${PN}-liblttng-ust-fork += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"

DEPENDS_${PN}-liblttng-ust-libc-wrapper += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"
RDEPENDS_${PN}-liblttng-ust-libc-wrapper += "libdl liblttng-ust \
	liblttng-ust-tracepoint librt"

DEPENDS_${PN}-liblttng-ust += "liblttng-ust-tracepoint librt"
RDEPENDS_${PN}-liblttng-ust += "liblttng-ust-tracepoint librt"
