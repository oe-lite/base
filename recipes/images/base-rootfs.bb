require base-rootfs.inc

RECIPE_FLAGS = "base_rootfs_jffs2_options"

inherit jffs2-image
DEFAULT_USE_base_rootfs_jffs2_options = "--faketime --squash"
JFFS2_IMAGE_OPTIONS = "${USE_base_rootfs_jffs2_options}"

RECIPE_FLAGS += "base_rootfs_ext2_options base_rootfs_ext2_size_in_blocks"

inherit ext2-image
DEFAULT_USE_base_rootfs_ext2_options = "-z -q -f"
DEFAULT_USE_base_rootfs_ext2_size_in_blocks = "10240"
EXT2_IMAGE_OPTIONS = "${USE_base_rootfs_ext2_options} -b ${USE_base_rootfs_ext2_size_in_blocks}"

inherit tar-image

inherit image-qa

RSTAGE_FIXUP_FUNCS += "do_version_install"

do_version_install () {
    if [ -n "$BUILD_TAG" ]; then
        echo $BUILD_TAG > ${SRCDIR}/build_tag
        install -m 0644 ${SRCDIR}/build_tag ${RSTAGE_DIR}${sysconfdir}/build_tag
    fi
}
