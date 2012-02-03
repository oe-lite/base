DESCRIPTION = "Berkeley DB 4.x"
HOMEPAGE = "http://www.oracle.com/us/products/database/berkeley-db/index.html"

SRC_URI = "http://download.oracle.com/berkeley-db/db-${PV}.tar.gz"

inherit autotools c++ largefile

DEPENDS = "libpthread"

B = "${S}/build_unix"

CONFIGURE_SCRIPT = "${S}/dist/configure"

EXTRA_OECONF += "--enable-compat185"
EXTRA_OECONF += "--enable-cxx --enable-stl"
EXTRA_OECONF += "--enable-pthread_api"

RECIPE_FLAGS += "db4_smallbuild"
EXTRA_OECONF += "${EXTRA_OECONF_SMALLBUILD}"
EXTRA_OECONF_SMALLBUILD = ""
EXTRA_OECONF_SMALLBUILD:USE_db4_smallbuild = "--enable-smallbuild"

EXTRA_OEMAKE += "prefix=${prefix} exec_prefix=${exec_prefix} bindir=${bindir} includedir=${includedir} libdir=${libdir} docdir=${docdir}/berkeley-db"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "db_archive db_checkpoint db_deadlock db_dump \
	db_hotbackup db_load db_printlog db_recover db_sql db_stat db_upgrade \
	db_verify"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "db db_cxx db_stl"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib:,-4.8,-4"
FILES_${PN}-libdb += "${libdir}/libdb-4.8.so"
FILES_${PN}-libdb-cxx += "${libdir}/libdb_cxx-4.8.so"
FILES_${PN}-libdb-stl += "${libdir}/libdb_stl-4.8.so"
PROVIDES_${PN}-libdb += "libdb4"
