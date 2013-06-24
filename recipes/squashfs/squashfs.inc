# -*- mode:python; -*-
DESCRIPTION = "A tool to generate squashfs filesystem as a normal (non-root) user."
LICENSE = "GPL"

inherit make c

DEPENDS += "zlib"

require conf/fetch/sourceforge.conf
SRC_URI = "http://downloads.sourceforge.net/project/squashfs/squashfs/squashfs${PV}/squashfs${PV}.tar.gz"

S = "${SRCDIR}/squashfs4.2/squashfs-tools/"

RECIPE_TYPES = "machine native sdk"

do_install() {
  mkdir -p ${D}/bin/
  install -m 0755 ${S}/mksquashfs ${D}/bin/
  install -m 0755 ${S}/unsquashfs ${D}/bin/
}
