SUMMARY = "libssh is a library written in C implementing the SSH protocol"
LICENSE = "LGPL-2.1"
SRC_URI = "https://red.libssh.org/attachments/download/195/libssh-${PV}.tar.xz"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine native"

inherit cmake c++
inherit library auto-package-libs

DEPENDS += "libc libz libssl libpthread libcrypto"
DEPENDS_${PN} += "libc libssl libz libcrypto"
RDEPENDS_${PN} += "libc libssl libz libcrypto"

AUTO_PACKAGE_LIBS = "ssh_threads"
AUTO_PACKAGE_LIBS_DEPENDS += "libpthread libssh"
AUTO_PACKAGE_LIBS_RDEPENDS += "libpthread libssh"

FILES_${PN}-dev += "${libdir}/cmake/${PN}"
