# -*- mode:python; -*-

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/linux/kernel/v2.6/linux-${PV}.tar.bz2"
S = "${SRCDIR}/linux-${PV}"
