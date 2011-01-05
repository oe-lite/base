require base-rootfs.inc

RECIPE_OPTIONS = "base_rootfs_ext2_options base_rootfs_ext2_size_in_blocks"

inherit ext2-image
DEFAULT_CONFIG_base_rootfs_ext2_options = "-z -q -f"
DEFAULT_CONFIG_base_rootfs_ext2_size_in_blocks = "10240"
EXT2_IMAGE_OPTIONS = "${RECIPE_OPTION_base_rootfs_ext2_options} -b ${RECIPE_OPTION_base_rootfs_ext2_size_in_blocks}"

inherit tar-image
