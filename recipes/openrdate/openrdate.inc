DESCRIPTION = "Date and time setting software implementing RFC 868 and RFC 2030 protocols"
HOMEPAGE = "http://sourceforge.net/projects/openrdate/"

COMPATIBLE_HOST_ARCHS = ".*linux"

LICENSE = "BSD-style"

require conf/fetch/sourceforge.conf

SRC_URI = "${SOURCEFORGE_MIRROR}/openrdate/openrdate-${PV}.tar.gz \
           file://debian.patch"

inherit autotools
