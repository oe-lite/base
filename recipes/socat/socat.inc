DESCRIPTION = "Socat is a relay for bidirectional data transfer between two independent data channels."
LICENSE = "GPL-2.0+-with-OpenSSL-exception"

inherit autotools auto-package-utils

RECIPE_TYPES = "machine"

SRC_URI = "http://www.dest-unreach.org/socat/download/socat-${PV}.tar.bz2"

COMPATIBLE_HOST_ARCHS = ".*linux"

AUTO_PACKAGE_UTILS = "socat filan procan"

DEPENDS_${PN}-socat = "libc"
RDEPENDS_${PN}-socat = "libc"
DEPENDS_${PN}-filan = "libc"
RDEPENDS_${PN}-filan = "libc"
DEPENDS_${PN}-procan = "libc"
RDEPENDS_${PN}-procan = "libc"
