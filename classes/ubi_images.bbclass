DEPENDS += "mtd-utils-native"

inherit files
inherit images

IMAGE_FILE = "${IMAGE_DEPLOY_DIR}/${PN}-${EPV}.ubi"

create_image() {
	#FIXME: move configuration to bb or conf file
	#FIXME: No support for several images in one ubi
	cat > $2.ini <<EOF
[ubifs]
mode=ubi
image=$2.ubifs
vol_id=0
vol_type=dynamic
vol_name=ubi
vol_flags=autoresize
EOF
	mkfs.ubifs -r $1 -o $2.ubifs \
		--leb-size=${NAND_LEB_SIZE} \
		--max-leb-cnt=${NAND_MAX_LEB_CNT} \
		--min-io-size=${NAND_MIN_IO_SIZE} \
	|| return 1

	ubinize -o $2 \
		--peb-size=${NAND_PEB_SIZE} \
		--sub-page-size=${NAND_SUB_PAGE_SIZE} \
		--min-io-size=${NAND_MIN_IO_SIZE} \
		$2.ini \
	|| return 1
}
