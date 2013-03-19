DESCRIPTION = "Control and monitor storage systems using S.M.A.R.T."
LICENSE = "GPL"

inherit c c++ autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.gz"

S = "${SRCDIR}/${PN}-${PV}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "smartd smartctl"
