# -*- mode:python; -*-
DESCRIPTION = "Userspace RCU - liburcu is a userspace RCU (read-copy-update) \
	library."
LICENSE = "LGPLv2.1"

RECIPE_TYPES = "machine"

inherit autotools-autoreconf auto-package-libs

SRC_URI = "http://lttng.org/files/urcu/userspace-rcu-${PV}.tar.bz2"

# Recipe build dependencies
DEPENDS = "libpthread"
AUTO_PACKAGE_LIBS = "urcu-bp urcu-cds urcu-common urcu urcu-mb urcu-qsbr \
	urcu-signal"
AUTO_PACKAGE_LIBS_PCPREFIX = "lib"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc libpthread ${PN}-dev"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS += "libc-dev libpthread-dev ${PN}-dev"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libpthread"
#DEPENDS_${PN} += "${LIBS_AUTO_RPACKAGES}"
#RDEPENDS_${PN} += "${LIBS_AUTO_RPACKAGES}"
DEPENDS_${PN}-liburcu-bp += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu-bp += "liburcu-common-${LIBRARY_VERSION}"
DEPENDS_${PN}-liburcu-cds += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu-cds += "liburcu-common-${LIBRARY_VERSION}"
DEPENDS_${PN}-liburcu += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu += "liburcu-common-${LIBRARY_VERSION}"
DEPENDS_${PN}-liburcu-mb += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu-mb += "liburcu-common-${LIBRARY_VERSION}"
DEPENDS_${PN}-liburcu-qsbr += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu-qsbr += "liburcu-common-${LIBRARY_VERSION}"
DEPENDS_${PN}-liburcu-signal += "liburcu-common-${LIBRARY_VERSION}"
RDEPENDS_${PN}-liburcu-signal += "liburcu-common-${LIBRARY_VERSION}"
