IMAGES = "initramfs-image archive-image"

RDEPENDS = "\
initramfs-init \
util/ssh util/scp \
"

PROVIDES_${PN} = "initramfs"

inherit rootfs cpio-image

PROVIDES_${PN} = ""
