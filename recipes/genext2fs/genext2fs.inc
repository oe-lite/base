LICENSE = "GPL"
DESCRIPTION = "A tool to generate an ext2 filesystem as a normal (non-root) user."
SECTION = "console/utils"

inherit autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/genext2fs/genext2fs-${PV}.tar.gz"

BBCLASSEXTEND = "native sdk"
