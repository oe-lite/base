inherit files
inherit images

IMAGE_EXT = '.tar'

create_image() {
	tar -C $1 -cf $2 . \
	|| return 1
}
