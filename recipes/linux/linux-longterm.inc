KERNEL_VERSION_SUBLEVEL = "${@'.'.join(d.get('PV').split('.')[:3])}"
SRC_URI = "${KERNELORG_MIRROR}/linux/kernel/v${KERNEL_VERSION_PATCHLEVEL}/longterm/v${KERNEL_VERSION_SUBLEVEL}/linux-${PV}.tar.bz2"
