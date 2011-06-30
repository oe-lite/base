inherit u-boot
DEPENDS = "u-boot-tools-native-mkimage"
SRC_URI = "git://git.denx.de/u-boot.git;protocol=git;tag=${PV}"
S = "${SRCDIR}/git"
UBOOT_ARCH = "${KERNEL_ARCH}"
