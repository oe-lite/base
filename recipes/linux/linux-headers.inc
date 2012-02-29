# -*- mode:python; -*-
inherit kernel-headers

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/linux/kernel/v${KERNEL_VERSION_PATCHLEVEL}/linux-${PV}.tar.bz2"
S = "${SRCDIR}/linux-${PV}"

DEFAULT_PREFERENCE = "1"
