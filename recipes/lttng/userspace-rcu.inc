# -*- mode:python; -*-
DESCRIPTION = "Userspace RCU - liburcu is a userspace RCU (read-copy-update) \
	library."
LICENSE = "LGPLv2.1"

RECIPE_TYPES = "machine"

inherit library autotools-autoreconf

SRC_URI = "http://lttng.org/files/urcu/userspace-rcu-${PV}.tar.bz2"

# Recipe build dependencies
DEPENDS = "libpthread"

# Package dependencies
LIBRARY_NAME = "liburcu"
DEPENDS_${PN} += "libpthread"

# Also providing these libraries
PROVIDES_${PN} += "liburcu-bp liburcu-cds liburcu-common liburcu-mb \
	liburcu-qsbr liburcu-signal"
