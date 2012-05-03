DESCRIPTION = "Zlib Compression Library"
HOMEPAGE = "http://www.gzip.org/zlib/"
LICENSE = "zlib"

RECIPE_TYPES = "machine native sdk"

inherit autotools library

SRC_URI = "http://www.zlib.net/zlib-${PV}.tar.bz2"

export CHOST="${CC}"

autotools_configure() {
    export LDSHAREDLIBC="-L${STAGE_DIR}/machine${stage_base_libdir} -lc"
    arch="${TARGET_CPU}"
    flag_64=""
    case $arch in
    x86_64)
      flag_64="--64"
      ;;
    esac
	./configure \
	$flag_64 \
	--prefix=${prefix} \
	--eprefix=${exec_prefix} \
	--libdir=${libdir} \
	--sharedlibdir=${sharedlibdir} \
	--includedir=${includedir}
}

LIBRARY_NAME = "libz"

RDEPENDS_${PN} = "libc libgcc"

FILES_${PN} += "${base_libdir}/lib*${SOLIBS} ${libdir}/lib*${SOLIBS}" 
