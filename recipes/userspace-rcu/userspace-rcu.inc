DESCRIPTION = "Userspace RCU - liburcu is a userspace RCU (read-copy-update) library."
SECTION = "libs"
PRIORITY = "optional"
LICENSE = "LGPLv2.1"

PR = "r1"

SRC_URI = "http://lttng.org/files/urcu/userspace-rcu-${PV}.tar.bz2"

S = "${WORKDIR}/userspace-rcu-${PV}"

inherit autotools

DEPENDS =+ "${TARGET_ARCH}/sysroot-libpthread"

PROVIDES_${PN}-dev += "liburcu"
DEPENDS_${PN}-dev = "${PN}"

RPROVIDES_${PN} += "liburcu"
