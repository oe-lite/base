DESCRIPTION = "execline is a (non-interactive) scripting language, like sh ; but its syntax is quite different from a traditional shell syntax."
LICENSE = "ISC"

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

inherit c make

DEPENDS += "libskarnet"

do_configure() {
	./configure \
		--prefix=${prefix} \
		--exec-prefix=${exec_prefix} \
		--bindir=${base_bindir} \
		--sbindir=${base_sbindir} \
		--libexecdir=${libexecdir} \
		--libdir=${libdir} \
		--includedir=${includedir} \
		--datadir=${datadir} \
		--with-sysdeps=${STAGE_DIR}/${HOST_TYPE}${libdir}/skalibs/sysdeps \
		--with-lib=${STAGE_DIR}/${HOST_TYPE}${libdir} \
		--with-dynlib=${STAGE_DIR}/${HOST_TYPE}${sharedlibdir} \
		--enable-shared --disable-allstatic \
		${HOST_ARCH}
}

PACKAGES = "${PN}-dbg ${PN}"

DEPENDS_${PN} += "libc libskarnet libexecline"
RDEPENDS_${PN} += "libc libskarnet libexecline"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "execline"
LIBRARY_VERSION = "2"
DEPENDS_${PN}-libexecline += "libc libskarnet"
RDEPENDS_${PN}-libexecline += "libc libskarnet"
FILES_${PN}-libexecline-dev += "${includedir}"
