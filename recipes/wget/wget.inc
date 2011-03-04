DESCRIPTION = "A console URL download utility featuring HTTP, FTP, and more."
LICENSE = "GPLv3"

DEPENDS = "${HOST_ARCH}/sysroot-librt"

inherit autotools gettext

require conf/fetch/gnu.conf

SRC_URI = "${GNU_MIRROR}/wget/wget-${PV}.tar.gz"

# Disable checking for SSL since that searches the system paths
EXTRA_OECONF = "--enable-ipv6 --without-ssl"

RPROVIDES_${PN} = "util/wget"
