DESCRIPTION = "a dependency-based init script management system"

require skaware.inc

SRC_URI_base = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"

RECIPE_FLAGS += "s6_rc_srcrev"
SRC_URI_base:USE_s6_rc_srcrev = "git://github.com/skarnet/s6-rc.git;${USE_s6_rc_srcrev}"
S:USE_s6_rc_srcrev = "${SRCDIR}/${PN}"

SRC_URI = "${SRC_URI_base}"

RECIPE_TYPES = "machine native"

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
		--host=${HOST_ARCH} \
		--build=${BUILD_ARCH}
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
