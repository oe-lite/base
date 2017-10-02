DESCRIPTION = "s6 is a small suite of programs for UNIX, designed to allow \
process supervision (a.k.a service supervision), in the line of daemontools \
and runit, as well as various operations on processes and daemons."

require skaware.inc

SRC_URI_base = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

RECIPE_FLAGS += "s6_srcrev"
SRC_URI_base:USE_s6_srcrev = "git://github.com/skarnet/s6.git;${USE_s6_srcrev}"
S:USE_s6_srcrev = "${SRCDIR}/${PN}"

SRC_URI = "${SRC_URI_base}"

RECIPE_TYPES = "machine native"

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
		--host=${HOST_ARCH} \
		--build=${BUILD_ARCH}
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
