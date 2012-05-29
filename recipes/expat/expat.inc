# -*- mode:python; -*-
DESCRIPTION = "Jim Clarkes XML parser library."
HOMEPAGE = "http://expat.sf.net/"

RECIPE_TYPES = "machine native sdk"

inherit autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/expat/expat-${PV}.tar.gz"

export LTCC = "${CC}"

RDEPENDS_${PN} = "libexpat"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "expat"
FILES_${PN}-libexpat-dev += "${includedir}"
FILES_${PN}-libexpat-dev:>TARGET_OS_mingw32 = " ${libdir}/libexpat.dll.a /usr/bin/libexpat-1.dll"
