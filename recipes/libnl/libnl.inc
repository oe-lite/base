DESCRIPTION = "libnl is a library for applications dealing with netlink sockets."
HOMEPAGE = "http://www.infradead.org/~tgr/libnl/"

LICENSE = "LGPLv2.1"

inherit autotools pkgconfig auto-package-libs auto-package-utils
DEPENDS += "libm libpthread libdl"

SRC_URI = "http://www.infradead.org/~tgr/${PN}/files/${PN}-${PV}.tar.gz"

AUTO_PACKAGE_UTILS = "\
n1-class-add nl-class-delete n1-class-lookup \
nl-class-list nl-cls-add nl-cls-delete nl-cls-list \
nl-link-list nl-pktloc-lookup nl-qdisc-add \
nl-qdisc-delete nl-qdisc-list"
