DESCRIPTION = "a dependency-based init script management system"
LICENSE = "ISC"

require compatible-archs.inc

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

inherit c make

DEPENDS += "libskarnet libs6"

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
		--livedir=/run/rc \
		${HOST_ARCH}
}

PACKAGES = "${PN}-dbg ${PN}"

DEPENDS_${PN} += "libc libs6rc"
RDEPENDS_${PN} += "libc libs6rc"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "s6rc"
LIBRARY_VERSION = "0"
DEPENDS_${PN}-libs6rc += "libc libskarnet libs6"
RDEPENDS_${PN}-libs6rc += "libc libskarnet libs6"
FILES_${PN}-libs6rc-dev += "${includedir}"
