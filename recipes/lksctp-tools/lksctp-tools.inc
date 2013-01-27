DESCRIPTION = "The Linux Kernel Stream Control Transmission Protocol (lksctp) project"

inherit autotools auto-package-utils auto-package-libs

DEPENDS += "libpthread libdl"
DEPENDS_${PN} += "libpthread libdl"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/lksctp/lksctp-tools-${PV}.tar.gz"
AUTO_PACKAGE_LIBS = "sctp"
AUTO_PACKAGE_UTILS = "checksctp sctp_darn sctp_status sctp_test withsctp"

