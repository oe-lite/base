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

AUTO_PACKAGE_LIBS = "lttng-ust lttng-ust-ctl lttng-ust-tracepoint \
	lttng-ust-cyg-profile lttng-ust-cyg-profile-fast \
	lttng-ust-libc-wrapper lttng-ust-fork"

AUTO_PACKAGE_LIBS_DEPENDS = "libc ${DEPENDS_LIBURCU}"
AUTO_PACKAGE_LIBS_RDEPENDS = "${AUTO_PACKAGE_LIBS_DEPENDS}"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${AUTO_PACKAGE_LIBS_DEPENDS} ${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev_${PV}"

DEPENDS_${PN}-liblttng-ust = "libdl librt liblttng-ust-tracepoint"
DEPENDS_${PN}-liblttng-ust-ctl = "libdl librt"
DEPENDS_${PN}-liblttng-ust-tracepoint = ""
DEPENDS_${PN}-liblttng-ust-cyg-profile = "libdl librt liblttng-ust"
DEPENDS_${PN}-liblttng-ust-cyg-profile-fast = "libdl librt liblttng-ust"
DEPENDS_${PN}-liblttng-ust-libc-wrapper = "libdl librt liblttng-ust"
DEPENDS_${PN}-liblttng-ust-fork = "libdl librt liblttng-ust"
