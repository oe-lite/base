# -*- mode:python; -*-
# dosfstools OE build file
# Copyright (C) 2004-2006, Advanced Micro Devices, Inc.  All Rights Reserved
# Released under the MIT license (see packages/COPYING)

DESCRIPTION = "DOS FAT Filesystem Utilities"
LICENSE = "GPL-3.0+"

RECIPE_TYPES = "machine native sdk"
COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

SRC_URI = "https://github.com/${PN}/${PN}/releases/download/v${PV}/${P}.tar.xz"
inherit c autotools

# output of getconf LFS_CFLAGS
#
CFLAGS += '-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64'

PACKAGES =+ "${PN}-mkfs ${PN}-fsck ${PN}-fslabel"

FILES_${PN}-mkfs = "${sbindir}/mkdosfs ${sbindir}/mkfs.*"
FILES_${PN}-fsck = "${sbindir}/dosfsck ${sbindir}/fsck.*"
FILES_${PN}-fslabel = "${sbindir}/dosfslabel"

PROVIDES_${PN}-mkfs = "util/mkfs.msdos util/mkfs.vfat util/mkdosfs"
PROVIDES_${PN}-fsck = "util/fsck.msdos util/fsck.vfat util/dosfsck"
PROVIDES_${PN}-fslabel = "util/dosfslabel"

DEPENDS_${PN}-mkfs = "libc libgcc"
RDEPENDS_${PN}-mkfs = "libc libgcc"
DEPENDS_${PN}-fsck = "libc libgcc"
RDEPENDS_${PN}-fsck = "libc libgcc"

RDEPENDS_${PN} = "libgcc libc ${PN}-mkfs ${PN}-fsck ${PN}-fslabel"
DEPENDS_${PN} = "libgcc libc ${PN}-mkfs ${PN}-fsck ${PN}-fslabel"
