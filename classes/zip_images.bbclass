inherit files
inherit images

DEPENDS_prepend += "zip-native"

IMAGE_EXT = '.zip'

create_image() {
	# zip do not support dangeling symlinks so remove them
	find -L . -type l -print0 | xargs -tr0 rm -f 
        
	zip -r $2 . \
	|| return 1
}
