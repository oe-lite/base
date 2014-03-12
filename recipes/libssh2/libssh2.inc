DESCRIPTION = "libssh2 is a client-side C library implementing the SSH2 protocol"
HOMEPAGE = "http://www.libssh2.org/"
LICENSE = "BSD-3-Clause"

RECIPE_TYPES = "machine"

inherit library autotools

DEPENDS += "libssl libgcrypt"
DEPENDS_${PN} += "libssl libgcrypt"
RDEPENDS_${PN} += "libssl libgcrypt"

SRC_URI += "http://www.libssh2.org/download/libssh2-${PV}.tar.gz"

LIBRARY_VERSION = "${@d.get('PV').split('.',1)[0]}"
