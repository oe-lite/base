DESCRIPTION = "s6 is a small suite of programs for UNIX, designed to allow \
process supervision (a.k.a service supervision), in the line of daemontools \
and runit, as well as various operations on processes and daemons."
LICENSE = "ISC"

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

inherit c make

DEPENDS += "libskarnet libexecline"

do_configure() {
	./configure \
		--prefix=${prefix} \
		--exec-prefix=${exec_prefix} \
		--bindir=${bindir} \
		--sbindir=${sbindir} \
		--libexecdir=${libexecdir} \
		--dynlibdir=${sharedlibdir} \
		--libdir=${libdir} \
		--includedir=${includedir} \
		--with-sysdeps=${STAGE_DIR}/${HOST_TYPE}${libdir}/skalibs/sysdeps \
		--with-lib=${STAGE_DIR}/${HOST_TYPE}${libdir} \
		--with-dynlib=${STAGE_DIR}/${HOST_TYPE}${sharedlibdir} \
		--enable-shared --disable-allstatic \
		${HOST_ARCH}
}

PACKAGES = "${PN}-dbg ${PN}"

DEPENDS_${PN} += "libc libs6"
RDEPENDS_${PN} += "libc libs6"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "s6"
LIBRARY_VERSION = "2"
DEPENDS_${PN}-libs6 += "libc libskarnet libexecline"
RDEPENDS_${PN}-libs6 += "libc libskarnet libexecline"
FILES_${PN}-libs6-dev += "${includedir}"
