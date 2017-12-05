# -*- mode:python; -*-
DESCRIPTION = "LTTng kernel modules"
LICENSE = "LGPLv2.1 GPLv2 MIT"

RECIPE_TYPES = "machine"

inherit kernel-modules
KERNEL_MODULES_COMPILE_MAKE_TARGETS = "default"

SRC_URI = "http://lttng.org/files/lttng-modules/lttng-modules-${PV}.tar.bz2"

PACKAGES = "${PN}"
FILES_${PN} = "/lib/modules"
