DESCRIPTION = "A library for applications dealing with netlink sockets"
HOMEPAGE = "http://www.infradead.org/~tgr/libnl/"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://www.infradead.org/~tgr/${PN}/files/${PN}-${PV}.tar.gz"

inherit autotools-autoreconf pkgconfig

DEPENDS += "libm ${DEPENDS_LIBC} native:bison native:flex"
DEPENDS_LIBC = "libpthread libdl"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

FILES_${PN}-dev += "${libdir}/libnl/cli/*/*.a"
FILES_${PN}-dev += "${libdir}/libnl/cli/*/*.la"
FILES_${PN}-dbg += "${libdir}/libnl/cli/*/.debug"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "nl-3 nl-route-3 nl-nf-3 nl-genl-3 nl-cli-3"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:,.0 ${sharedlibdir}:lib:,.0:"
AUTO_PACKAGE_LIBS_PCPREFIX = "lib"
FILES_${PN}-libnl-route-3 += "${sysconfdir}/libnl/"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
nl-class-add nl-class-delete nl-classid-lookup \
nl-class-list nl-cls-add nl-cls-delete nl-cls-list \
nl-link-list nl-pktloc-lookup nl-qdisc-add \
nl-qdisc-delete nl-qdisc-list"
AUTO_PACKAGE_UTILS_DEPENDS += "libc libdl libm libnl-3 libnl-cli-3 libnl-genl-3 \
			 libnl-nf-3 libnl-route-3 libpthread"
AUTO_PACKAGE_UTILS_RDEPENDS += "libdl libm libnl-3 libnl-cli-3 libnl-cli-3 \
			libnl-genl-3 libnl-nf-3 libnl-route-3 \
			libpthread"

AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc libm libpthread ${PN}-dev"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libm libpthread"
DEPENDS_${PN}-dev = ""
DEPENDS_${PN}-libnl-nf-3 += "libnl-route-3 libnl-3"
RDEPENDS_${PN}-libnl-nf-3 += "libnl-route-3 libnl-3"
DEPENDS_${PN}-libnl-route-3 += "libnl-3"
RDEPENDS_${PN}-libnl-route-3 += "libnl-3"
DEPENDS_${PN}-libnl-genl-3 += "libnl-3"
RDEPENDS_${PN}-libnl-genl-3 += "libnl-3"
DEPENDS_${PN}-libnl-cli-3 += "libnl-genl-3 libnl-nf-3 \
			libnl-route-3 libnl-3 libdl"
RDEPENDS_${PN}-libnl-cli-3 += "libnl-genl-3 libnl-nf-3 \
			libnl-route-3 libnl-3 libdl"
DEPENDS_${PN} += "libc libm ${DEPENDS_LIBC} libnl-3 libnl-cli-3 \
		libnl-genl-3 libnl-nf-3 libnl-route-3"
RDEPENDS_${PN} += "libm libpthread libc libdl libnl-3 libnl-cli-3 libnl-genl-3 \
		libnl-nf-3 libnl-route-3"
FILES_${PN}-libnl-cli-3 += "${libdir}/libnl/cli/*/*.so"
FILES_${PN}-libnl-cli-3-dev += "${libdir}/libnl/cli/*/*.a ${libdir}/libnl/cli/*/*.la"
