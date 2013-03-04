SUMMARY = "Linux Trace Toolkit Userspace Tracer 2.0"
DESCRIPTION = "The LTTng UST 2.0 package contains the userspace tracer library to trace userspace codes."
HOMEPAGE = "http://lttng.org/lttng2.0"

inherit c++ autotools-autoreconf

DEPENDS = "liburcu util-linux libuuid librt libdl"
SRC_URI = "http://lttng.org/files/lttng-ust/lttng-ust-${PV}.tar.bz2"

PACKAGES = "${PN}-dbg ${PN}-doc ${PN} ${PN}-dev ${PN}-locale ${PN}-demos"

FILES_${PN}-demos = "/tmp/"
FILES_${PN} += "${libdir}/*.so"

RDEPENDS_${PN} = "liburcu"
