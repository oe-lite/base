require base-rootfs.inc

RECIPE_OPTIONS = "base_rootfs_jffs2_options"

inherit jffs2-image
DEFAULT_CONFIG_base_rootfs_jffs2_options = "--faketime --squash"
JFFS2_IMAGE_OPTIONS = "${RECIPE_OPTION_base_rootfs_jffs2_options}"

inherit tar-image

inherit image-qa
