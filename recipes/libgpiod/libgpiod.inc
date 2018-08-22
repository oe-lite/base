# -*- mode:python; -*-
require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/software/libs/libgpiod/libgpiod-${PV}.tar.xz"

LICENSE = "LGPL-2.1+"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools
EXTRA_OECONF = "--enable-tools=yes"

inherit library
DEPENDS_${PN} = "libc"

PACKAGES =+ "${PN}-utils"
FILES_${PN}-utils = "${bindir}"
DEPENDS_${PN}-utils = "${PN}"
RDEPENDS_${PN}-utils = "${PN}"
