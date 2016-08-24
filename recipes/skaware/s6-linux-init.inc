DESCRIPTION = "s6-linux-init is a set of minimalistic tools to create an \
s6-based init system, including a /sbin/init binary, on a Linux kernel."
LICENSE = "ISC"

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

inherit c make

DEPENDS += "libskarnet"

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

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}"

DEPENDS_${PN} += "libc libskarnet"
RDEPENDS_${PN} += "libc libskarnet execline s6-portable-utils s6-linux-utils s6"
