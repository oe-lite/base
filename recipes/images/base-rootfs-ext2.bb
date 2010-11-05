require base-rootfs.inc

RECIPE_OPTIONS = "base_rootfs_ext2_options"

inherit ext2-image
DEFAULT_CONFIG_base_rootfs_ext2_options = "-z -q -f"
EXT2_IMAGE_OPTIONS = "${RECIPE_OPTION_base_rootfs_ext2_options}"

inherit tar-image
