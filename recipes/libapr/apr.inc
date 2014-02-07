DESCRIPTION="software libraries providing a predictable and consistent interface to underlying platform-specific implementations"
HOMEPAGE="apr.apache.org"

inherit autotools-autoreconf pkgconfig library binconfig

SRC_URI = "http://apache.mirrors.spacedump.net/apr/apr-${PV}.tar.bz2"

DEPENDS += "libdl libpthread"
DEPENDS_${PN} += "libc libgcc libdl libpthread"
RDEPENDS_${PN} += "libc libgcc libdl libpthread"

EXTRA_OECONF += "--disable-threads"

FILES_${PN}-dev += "${libdir}/apr.exp ${datadir}/build-1/*"
