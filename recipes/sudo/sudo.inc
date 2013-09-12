DESCRIPTION = "allows users to run programs with the security privileges of another user"

RECIPE_TYPES = "machine"

SRC_URI = "http://www.sudo.ws/sudo/dist/${PN}-${PV}.tar.gz"

inherit autotools pkgconfig auto-package-utils

DEPENDS += "libdl"

AUTO_PACKAGE_UTILS = "sudo sudoreplay visudo sudoedit"
AUTO_PACKAGE_UTILS_RDEPENDS += "${PN}"
DEPENDS_${PN}-sudo += "libdl"
RDEPENDS_${PN}-sudo += "libdl"

RDEPENDS_${PN}-sudoedit = "${PN}-sudo"
