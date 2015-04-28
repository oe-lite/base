DESCRIPTION="software libraries providing a predictable and consistent interface to underlying platform-specific implementations"
HOMEPAGE="apr.apache.org"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit autotools-autoreconf pkgconfig library binconfig

SRC_URI = "http://apache.mirrors.spacedump.net/apr/apr-${PV}.tar.bz2"

DEPENDS += "${DEPENDS_LIBC} libpthread"
DEPENDS_LIBC = "libdl"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS_${PN} += "libc libgcc ${DEPENDS_LIBC} libpthread"
RDEPENDS_${PN} += "libc libgcc ${DEPENDS_LIBC} libpthread"

EXTRA_OECONF += "--disable-threads"

FILES_${PN}-dev += "${libdir}/apr.exp ${datadir}/build-1/*"
