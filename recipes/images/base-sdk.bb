inherit canadian-cross sdk-image

IMAGE_BASENAME = "oe-lite-sdk-${HOST_ARCH}-${TARGET_ARCH}"
TAR_IMAGE_DIRNAME = "sdk"
ZIP_IMAGE_DIRNAME = "sdk"

RDEPENDS = " \
    ${TOOLCHAIN}-canadian-cross-gdb \
    ${TOOLCHAIN}-canadian-cross \
    ${TARGET_ARCH}/sysroot-libcrypt \
    ${TARGET_ARCH}/sysroot-libresolv \
    ${TARGET_ARCH}/sysroot-dev \
    ${TARGET_ARCH}/sysroot-libdl \
    ${TARGET_ARCH}/sysroot-librt \
    ${TARGET_ARCH}/sysroot-doc \
    ${TARGET_ARCH}/sysroot-libgcc \
    ${TARGET_ARCH}/sysroot-libstdc++ \
    ${TARGET_ARCH}/sysroot-garbage \
    ${TARGET_ARCH}/sysroot-libm \
    ${TARGET_ARCH}/sysroot-libutil \
    ${TARGET_ARCH}/sysroot-libnss-dns \
    ${TARGET_ARCH}/sysroot-locale \
    ${TARGET_ARCH}/sysroot-libnss-files \
    ${TARGET_ARCH}/sysroot-libc \
    ${TARGET_ARCH}/sysroot-libpthread \
"

RDEPENDS += "u-boot-mkimage-sdk"
