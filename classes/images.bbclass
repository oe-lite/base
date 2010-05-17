DEPENDS_prepend += "makedevs-native"

IMAGE_FILE = "${PN}-${EPV}-${MACHINE}-${DATETIME}${IMAGE_EXT}"
IMAGE_SYMLINK_FILE = "${PN}-${MACHINE}${IMAGE_EXT}"
FILES_${PN} = "/${IMAGE_FILE}"

makedevs_files() {
    if [ -d ${1}/${devtable} ]; then
        find ${1}/${devtable}/ -type f -print0 | xargs -r0 -n1 makedevs -r ${1} -D
    fi
}

fakeroot do_image_build() {
    set -x
    makedevs_files ${FILES_DIR}
    tar czf ${IMAGE_DEPLOY_DIR}/${IMAGE_FILE}.tar.gz ${FILES_DIR}
    [ -d etc ] && echo ${DATETIME} >etc/timestamp
    create_image ${FILES_DIR} ${D}/${IMAGE_FILE}
    [ -s ${D}/${IMAGE_FILE} ] || return 1
}
EXPORT_FUNCTIONS do_image_build
addtask image_build before do_package_install after do_files_fixup
do_image_build[dirs] = "${IMAGE_DEPLOY_DIR} ${FILES_DIR}"


do_image_deploy() {
    cp -f ${D}/${IMAGE_FILE}  ${IMAGE_DEPLOY_DIR}
    ln -fs ${IMAGE_FILE} ${IMAGE_DEPLOY_DIR}/${IMAGE_SYMLINK_FILE}
}
EXPORT_FUNCTIONS do_image_deploy
addtask image_deploy before do_package_install after do_image_build
do_image_deploy[dirs] = "${IMAGE_DEPLOY_DIR}"
