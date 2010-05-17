inherit files
inherit images

IMAGE_EXT = '.cpio'

create_image() {
	cd $1 && find . | cpio -o -H newc > $2 \
	|| return 1
}
