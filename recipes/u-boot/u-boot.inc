inherit u-boot
DEPENDS = "native:u-boot-tools-mkimage"
SRC_URI = "git://git.denx.de/u-boot.git;protocol=git;tag=${PV}"
S = "${SRCDIR}/u-boot"
UBOOT_ARCH = "${KERNEL_ARCH}"
