DESCRIPTION = "allows users to run programs with the security privileges of another user"

RECIPE_TYPES = "machine"
COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://www.sudo.ws/sudo/dist/${PN}-${PV}.tar.gz"

inherit autotools pkgconfig auto-package-utils

DEPENDS += "libdl libcrypt"

AUTO_PACKAGE_UTILS = "sudo sudoreplay visudo sudoedit"
AUTO_PACKAGE_UTILS_RDEPENDS += "${PN}"

FILES_sudo-sudo[qa] = "allow-elf-libs-in-other-dirs"
PROVIDES_${PN}-sudo[qa] = "allow-missing-provides:libsudo_noexec"
DEPENDS_${PN}-sudo += "libc libdl libcrypt"
RDEPENDS_${PN}-sudo += "libc libdl libcrypt"
DEPENDS_${PN}-sudoreplay = "libc"
RDEPENDS_${PN}-sudoreplay = "libc"
DEPENDS_${PN}-visudo = "libc"
RDEPENDS_${PN}-visudo = "libc"
RDEPENDS_${PN}-sudoedit = "${PN}-sudo"
