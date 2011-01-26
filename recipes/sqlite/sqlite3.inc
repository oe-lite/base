DESCRIPTION = "An Embeddable SQL Database Engine"
HOMEPAGE = "http://www.sqlite.org"
SECTION = "libs"
PRIORITY = "optional"
DEPENDS = "readline${RE}-dev \
           ncurses${RE}-dev \
           ${TARGET_ARCH}/sysroot-libpthread"
DEPENDS_recipe-native = "tcl-native"

LICENSE = "PD"

BBCLASSEXTEND = "native"

inherit autotools pkgconfig

SRC_URI = "http://www.sqlite.org/sqlite-${PV}.tar.gz \
	   file://libtool.patch"

S = "${SRCDIR}/sqlite-${PV}"


EXTRA_OECONF = "--disable-tcl --enable-shared \
		--enable-threadsafe"

export config_BUILD_CC = "${BUILD_CC}"
export config_BUILD_CFLAGS = "${BUILD_CFLAGS}"
export config_BUILD_LIBS = "${BUILD_LDFLAGS}"
export config_TARGET_CC = "${CC}"
export config_TARGET_LINK = "${CCLD}"
export config_TARGET_CFLAGS = "${CFLAGS}"
export config_TARGET_LFLAGS = "${LDFLAGS}"

FILES_${PN} = "${bindir}/*"
FILES_${PN} = "${libdir}/*.so.*"
FILES_${PN}-dev = "${libdir}/*.a ${libdir}/*.la ${libdir}/*.so \
		       ${libdir}/pkgconfig ${includedir}"
FILES_${PN}-doc = "${docdir} ${mandir} ${infodir}"

