RECIPE_TYPES = "canadian-cross"
inherit sdk-image

IMAGE_BASENAME = "oe-lite-sdk-${HOST_ARCH}-${TARGET_ARCH}"
TAR_IMAGE_DIRNAME = "sdk"
ZIP_IMAGE_DIRNAME = "sdk"

RDEPENDS = " \
    gcc-canadian-cross-gdb \
    gcc-canadian-cross \
    libcrypt \
    libresolv \
    dev \
    libdl \
    librt \
    doc \
    libgcc \
    libstdc++ \
    garbage \
    libm \
    libutil \
    libnss-dns \
    locale \
    libnss-files \
    libc \
    libpthread \
    ${U_BOOT_MKIMAGE} \
"

U_BOOT_MKIMAGE="u-boot-tools-sdk-mkimage"
U_BOOT_MKIMAGE_host-mingw32 = ""
