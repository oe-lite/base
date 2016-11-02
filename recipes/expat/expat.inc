# -*- mode:python; -*-
DESCRIPTION = "Jim Clarkes XML parser library."
HOMEPAGE = "http://expat.sf.net/"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath

#Only used for Aarch64
AUTOCONFDIRS = "/conftools"

export LTCC = "${CC}"

DEPENDS_${PN} = "libc libgcc libexpat"
RDEPENDS_${PN} = "libc libgcc libexpat"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "expat"
FILES_${PN}-libexpat-dev += "${includedir}"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libgcc"
DEPENDS_${PN}-libexpat = "libc libgcc"
