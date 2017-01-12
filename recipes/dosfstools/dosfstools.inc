# -*- mode:python; -*-
# dosfstools OE build file
# Copyright (C) 2004-2006, Advanced Micro Devices, Inc.  All Rights Reserved
# Released under the MIT license (see packages/COPYING)

DESCRIPTION = "DOS FAT Filesystem Utilities"
LICENSE = "GPL-3.0+"

RECIPE_TYPES = "machine native sdk"
COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

SRC_URI = "https://github.com/${PN}/${PN}/releases/download/v${PV}/${P}.tar.xz"
inherit c autotools pkgconfig

# output of getconf LFS_CFLAGS
#
CFLAGS += '-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64'

inherit auto-package-utils

AUTO_PACKAGE_UTILS = "fatlabel fsck.fat mkfs.fat"
AUTO_PACKAGE_UTILS_DEPENDS += "libc libgcc"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc libgcc"

# Legacy provides for backward compatibility
PROVIDES_${PN}-mkfs.fat += "util/mkfs.msdos util/mkfs.vfat util/mkdosfs"
PROVIDES_${PN}-fsck.fat += "util/fsck.msdos util/fsck.vfat util/dosfsck"
PROVIDES_${PN}-fatlabel += "util/dosfslabel"

RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PACKAGES}"
DEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PACKAGES}"
