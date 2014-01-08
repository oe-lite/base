DESCRIPTION = "The Linux Kernel Stream Control Transmission Protocol (lksctp) project"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools auto-package-utils auto-package-libs

DEPENDS += "libpthread libdl"
DEPENDS_${PN} += "libpthread libdl"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/lksctp/lksctp-tools-${PV}.tar.gz"
AUTO_PACKAGE_LIBS = "sctp"
AUTO_PACKAGE_UTILS = "checksctp sctp_darn sctp_status sctp_test withsctp"
AUTO_PACKAGE_UTILS_DEPENDS += "libc"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc"
DEPENDS_${PN}-libsctp += "libc"
RDEPENDS_${PN}-libsctp += "libc"
DEPENDS_${PN}-sctp-darn += "libsctp"
RDEPENDS_${PN}-sctp-darn += "libsctp"
DEPENDS_${PN}-sctp-status += "libsctp"
RDEPENDS_${PN}-sctp-status += "libsctp"
DEPENDS_${PN}-sctp-test += "libsctp"
RDEPENDS_${PN}-sctp-test += "libsctp"
