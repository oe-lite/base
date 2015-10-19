DESCRIPTION = "Database Drivers for libdbi"
HOMEPAGE = "http://libdbi-drivers.sourceforge.net/"
LICENSE = "LGPLv2.1+"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/libdbi-drivers/libdbi-drivers-${PV}.tar.gz \
	file://sqlite3-naming.patch"

inherit autotools

DEPENDS += "libdbi libdbi-dev sqlite3-libsqlite3 sqlite3-libsqlite3-dev"
RDEPENDS_${PN} += "libdbi sqlite3-libsqlite3"

COMPATIBLE_HOST_ARCHS = ".*linux"

PACKAGES += "libdbd-sqlite3"

EXTRA_OECONF = "--with-dbi-incdir=${STAGE_DIR}/${HOST_TYPE}${includedir} \
                --with-dbi-libdir=${STAGE_DIR}/${HOST_TYPE}${libdir} \
                --with-sqlite3 \
                --with-sqlite3-incdir=${STAGE_DIR}/${HOST_TYPE}${includedir} \
                --with-sqlite3-libdir=${STAGE_DIR}/${HOST_TYPE}${libdir} \
                --disable-docs"

FILES_${PN}-dbg += " ${libdir}/dbd/.debug/*.so"
FILES_${PN}-dev += " ${libdir}/dbd/*.la \
		${libdir}/dbd/*.a"

FILES_libdbd-sqlite3 = "${libdir}/dbd/libdbdsqlite3.so"
