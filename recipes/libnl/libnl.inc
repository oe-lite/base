DESCRIPTION = "A library for applications dealing with netlink sockets"
HOMEPAGE = "http://www.infradead.org/~tgr/libnl/"

SRC_URI = "http://www.infradead.org/~tgr/${PN}/files/${PN}-${PV}.tar.gz"

inherit autotools-autoreconf pkgconfig

DEPENDS += "libm libpthread libdl"
DEPENDS_${PN} += "libm libpthread libdl"

FILES_${PN}-dbg += "${libdir}/libnl/cli/*/.debug"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "nl-3 nl-route-3 nl-nf-3 nl-genl-3 nl-cli-3"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:,.0 ${sharedlibdir}:lib:,.0:"
AUTO_PACKAGE_LIBS_PCPREFIX = "lib"
RDEPENDS_${PN}-libnl-nf-3 += "libnl-3 libnl-route-3"
RDEPENDS_${PN}-libnl-cli-3 += "libnl-3 libnl-route-3 libnl-genl-3 libnl-nf-3"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
nl-class-add nl-class-delete nl-classid-lookup \
nl-class-list nl-cls-add nl-cls-delete nl-cls-list \
nl-link-list nl-pktloc-lookup nl-qdisc-add \
nl-qdisc-delete nl-qdisc-list"
AUTO_PACKAGE_UTILS_RDEPENDS += "libnl-route-3 libnl-genl-3 libnl-nf-3"

RDEPENDS_${PN} += "libm libpthread libc"
AUTO_PACKAGE_UTILS_RDEPENDS += "${PN} libnl-3"
