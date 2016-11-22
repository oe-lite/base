DESCRIPTION = "Berkeley DB 6.x"
HOMEPAGE = "http://www.oracle.com/us/products/database/berkeley-db/index.html"

SRC_URI = "http://download.oracle.com/berkeley-db/db-${PV}.tar.gz"

LICENSE = "AGPL-1.0"

inherit autotools c++ largefile

DEPENDS = "${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

B = "${S}/build_unix"

CONFIGURE_SCRIPT = "${S}/dist/configure"

EXTRA_OECONF += "--enable-compat185"
EXTRA_OECONF += "--enable-cxx --enable-stl"
EXTRA_OECONF += "--enable-pthread_api"

RECIPE_FLAGS += "db_smallbuild"
EXTRA_OECONF += "${EXTRA_OECONF_SMALLBUILD}"
EXTRA_OECONF_SMALLBUILD = ""
EXTRA_OECONF_SMALLBUILD:USE_db_smallbuild = "--enable-smallbuild"

EXTRA_OEMAKE += "prefix=${prefix} exec_prefix=${exec_prefix} bindir=${bindir} includedir=${includedir} libdir=${libdir} docdir=${docdir}/berkeley-db"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "db_archive db_checkpoint db_deadlock db_dump \
	db_hotbackup db_load db_log_verify db_printlog db_recover \
	db_replicate db_sql db_stat db_tuner db_upgrade db_verify"

AUTO_PACKAGE_UTILS_DEPENDS += "libc libpthread libdb"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc libpthread libdb"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "db db_cxx db_stl"
PROVIDES_${PN}-libdb += "libdb6"
