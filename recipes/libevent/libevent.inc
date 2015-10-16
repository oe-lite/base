DESCRIPTION = "libevent - an asynchronous event notification library"
HOMEPAGE = "http://libevent.org"
LICENSE = "BSD-3-Clause"

inherit autotools

DEPENDS += "libm"

SRC_URI = "https://github.com/libevent/libevent/releases/download/release-${PV}-stable/libevent-${PV}-stable.tar.gz"

S = "${SRCDIR}/libevent-${PV}-stable"

# vim: set syntax=bitbake :
