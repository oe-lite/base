inherit autotools

#Only used for Aarch64
AUTOCONFDIRS = "/ \
                /config"

DESCRIPTION = "kexec-tools: User-space tools for using the kexec feature of Linux"
HOMEPAGE = "https://www.kernel.org/pub/linux/utils/kernel/kexec/"
LICENSE = "GPL-2.0"
SRC_URI = "https://www.kernel.org/pub/linux/utils/kernel/kexec/kexec-tools-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS=".*linux"
