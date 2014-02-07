DESCRIPTION = "software libraries providing a predictable and consistent interface to underlying platform-specific implementations"
HOMEPAGE = "apr.apache.org"

inherit autotools-autoreconf pkgconfig library binconfig c

SRC_URI = "http://apache.mirrors.spacedump.net/apr/apr-util-${PV}.tar.bz2"

DEPENDS += "libapr-dev libapr libexpat libdl libcrypt"
DEPENDS_${PN} += "libapr libdl libexpat libcrypt"
RDEPENDS_${PN} += "libapr libdl libexpat libcrypt"

EXTRA_OECONF = "--with-apr=${HOST_SYSROOT}/usr/bin/apr-1-config\
	        --without-odbc \
		--without-pgsql \
		--without-sqlite2 \
		--without-sqlite3 \
		--with-expat=${HOST_SYSROOT} \
		"
CFLAGS += "-I${HOST_SYSROOT}${includedir} -Wl,-lcrypt"

do_configure[postfuncs] = "do_configure_apr"

do_configure_apr() {
	cp ${HOST_SYSROOT}/usr/share/build-1/apr_rules.mk ${S}/build/rules.mk
	sed -i "s#apr_builddir=#apr_builddir=${HOST_SYSROOT}#" ${S}/build/rules.mk
	sed -i "s#apr_builders=#apr_builders=${HOST_SYSROOT}#" ${S}/build/rules.mk
	sed -i "s#top_builddir=#top_builddir=${HOST_SYSROOT}#" ${S}/build/rules.mk
}

LIBRARY_NAME = "libaprutil"

FILES_${PN}-dev += "${libdir}/aprutil.exp ${datadir}/build-1/*"

PROVIDES_${PN} = "libaprutil"
