DESCRIPTION = "s6-linux-utils is a set of minimalistic Linux-specific system \
utilities."

require skaware.inc

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

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
		--datadir=${datadir} \
		--with-sysdeps=${STAGE_DIR}/${HOST_TYPE}${libdir}/skalibs/sysdeps \
		--with-lib=${STAGE_DIR}/${HOST_TYPE}${libdir} \
		--with-dynlib=${STAGE_DIR}/${HOST_TYPE}${sharedlibdir} \
		--enable-shared --disable-allstatic \
		${HOST_ARCH}
}

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}"

DEPENDS_${PN} += "libc libskarnet"
RDEPENDS_${PN} += "libc libskarnet"
