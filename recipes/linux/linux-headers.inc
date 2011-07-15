inherit kernel-headers

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/pub/linux/kernel/v${KERNEL_VERSION_PATCHLEVEL}/linux-${PV}.tar.bz2"
S = "${SRCDIR}/linux-${PV}"
