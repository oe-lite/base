DESCRIPTION = "Jim Clarkes XML parser library."
HOMEPAGE = "http://expat.sf.net/"
SECTION = "libs"
LICENSE = "MIT"

PR = "r1"

BBCLASSEXTEND = "native sdk"

SRC_URI = "${SOURCEFORGE_MIRROR}/expat/expat-${PV}.tar.gz"
S = "${WORKDIR}/expat-${PV}"

export LTCC = "${CC}"

inherit autotools
