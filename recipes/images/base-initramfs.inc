IMAGES = "initramfs-image tar-image"

RDEPENDS = "\
initramfs-init \
util/ssh util/scp \
"

PROVIDES_${PN} = "initramfs"

inherit rootfs