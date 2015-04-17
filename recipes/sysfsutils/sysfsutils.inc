DESCRIPTION = "System Utilities Based on Sysfs"
HOMEPAGE = "http://linux-diag.sourceforge.net/Sysfsutils.html"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/linux-diag/sysfsutils-${PV}.tar.gz"

acpaths = "-I ${S}/m4"

PACKAGES = "${PN}-libsysfs ${PN}-libsysfs-dbg ${PN}-libsysfs-dev \
	    ${PN} ${PN}-dbg ${PN}-doc ${PN}-locale"

FILES_${PN}-libsysfs = "${libdir}/*.so.*"
FILES_${PN}-libsysfs-dev = "${includedir} ${libdir}/lib*.so ${libdir}/*.la \
		     ${libdir}/*.a"
FILES_libsysfs-dbg += "${libdir}/.debug"
