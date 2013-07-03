DESCRIPTION = "Zlib Compression Library"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

RECIPE_TYPES = "machine native sdk"

inherit c libtool make library

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

do_configure() {
	if [ '${HOST_OS}' = 'mingw32' ] ; then
		cp win32/Makefile.gcc Makefile
	else
		if [ -f Makefile ] ; then
			${MAKE} distclean
		fi
		CHOST=${HOST_ARCH} ./configure \
			--prefix=${prefix} --eprefix=${exec_prefix} \
			--libdir=${libdir} --includedir=${includedir}
	fi
}

EXTRA_OEMAKE:HOST_LIBC_mingw = "PREFIX=${HOST_PREFIX}"

EXTRA_OEMAKE_INSTALL:HOST_LIBC_mingw = "BINARY_PATH=${sharedlibdir} INCLUDE_PATH=${includedir} LIBRARY_PATH=${libdir} SHARED_MODE=1"

FILES_${PN}:>HOST_LIBC_mingw = " ${sharedlibdir}/*.dll"

LIBRARY_NAME = "libz"

RDEPENDS_${PN} = "libc libgcc"
