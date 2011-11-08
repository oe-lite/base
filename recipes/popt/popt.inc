# -*- mode:python; -*-
DESCRIPTION = "Command line option parsing library"
LICENSE = "MIT"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath library largefile

SRC_URI = "http://rpm5.org/files/popt/popt-${PV}.tar.gz"

LIBRARY_DEPENDS = ""

# Recipe build dependencies
DEPENDS =+ "${LIBRARY_DEPENDS}"

# Package dependencies
DEPENDS_${PN} += "${LIBRARY_DEPENDS}"
RDEPENDS_${PN} += "${LIBRARY_DEPENDS}"
