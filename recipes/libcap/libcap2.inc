# -*- mode:python; -*-
DESCRIPTION = "Libcap is a library for getting and setting POSIX.1e \
	(formerly POSIX 6) draft 15 capabilities."
LICENSE = "GPL,BSD"

RECIPE_TYPES = "machine"

inherit make c library auto-package-utils

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/linux/libs/security/linux-privs/libcap2/libcap-${PV}.tar.bz2"

S = "${SRCDIR}/libcap-${PV}"

DEPENDS = "native:bison native:flex libattr"

BUILD_CFLAGS += "-I${S}/libcap/include"

do_install() {
        oe_runmake DESTDIR="${D}" prefix="${prefix}" libdir="${libdir}" RAISE_SETFCAP=no install
}

DEPENDS_${PN} = "libattr"

AUTO_PACKAGE_UTILS = "capsh getcap getpcaps setcap"
AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}"
