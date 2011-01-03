DESCRIPTION = "Jim Clarkes XML parser library."
HOMEPAGE = "http://expat.sf.net/"
SECTION = "libs"
LICENSE = "MIT"

BBCLASSEXTEND = "native sdk"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/expat/expat-${PV}.tar.gz"

export LTCC = "${CC}"

inherit autotools
