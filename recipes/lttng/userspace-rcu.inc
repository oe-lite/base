DESCRIPTION = "Userspace RCU - liburcu is a userspace RCU (read-copy-update) library."
SECTION = "libs"
PRIORITY = "optional"
LICENSE = "LGPLv2.1"

SRC_URI = "http://lttng.org/files/urcu/userspace-rcu-${PV}.tar.bz2"

S = "${WORKDIR}/userspace-rcu-${PV}"

inherit autotools

# Recipe build dependencies
DEPENDS =+ "${TARGET_ARCH}/sysroot-libpthread"

# Package build dependencies
PROVIDES_${PN}-dev += "liburcu"
DEPENDS_${PN}-dev = "${PN} ${TARGET_ARCH}/sysroot-libpthread"

# Package run-time dependencies
RPROVIDES_${PN} += "liburcu"
RDEPENDS_${PN} = "${TARGET_ARCH}/sysroot-libpthread"
RDEPENDS_${PN}-dev = "${PN}"
