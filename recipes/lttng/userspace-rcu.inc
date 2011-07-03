# -*- mode:python; -*-
DESCRIPTION = "Userspace RCU - liburcu is a userspace RCU (read-copy-update) \
	library."
LICENSE = "LGPLv2.1"

RECIPE_TYPES = "machine"

inherit autotools library

SRC_URI = "http://lttng.org/files/urcu/userspace-rcu-${PV}.tar.bz2"

# Recipe build dependencies
DEPENDS = "libpthread"

# Package dependencies
PROVIDES_${PN} = "liburcu"
PROVIDES_${PN}-dev = "liburcu-dev"
DEPENDS_${PN} += "libpthread"
