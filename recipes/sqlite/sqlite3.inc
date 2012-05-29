# -*- mode:python; -*-
DESCRIPTION = "An Embeddable SQL Database Engine"
HOMEPAGE = "http://www.sqlite.org"

RECIPE_TYPES = "machine"

inherit autotools pkgconfig

RECIPE_FLAGS += "sqlite3_largefile"
EXTRA_OECONF_LARGEFILE = "--disable-largefile"
EXTRA_OECONF_LARGEFILE:USE_sqlite3_largefile = "--enable-largefile"
EXTRA_OECONF += "${EXTRA_OECONF_LARGEFILE}"

RECIPE_FLAGS += "sqlite3_threadsafe"
EXTRA_OECONF_THREADSAFE = "--disable-threadsafe"
EXTRA_OECONF_THREADSAFE:USE_sqlite3_threadsafe = "--enable-threadsafe"
EXTRA_OECONF += "${EXTRA_OECONF_THREADSAFE}"
DEPENDS:>USE_sqlite3_threadsafe = " libpthread"
DEFAULT_USE_sqlite3_threadsafe = "1"

RECIPE_FLAGS += "sqlite3_readline"
EXTRA_OECONF_READLINE = "--disable-readline"
EXTRA_OECONF_READLINE:USE_sqlite3_readline = "--enable-readline"
EXTRA_OECONF += "${EXTRA_OECONF_READLINE}"
DEPENDS:>USE_sqlite3_readline = " libreadline"
DEFAULT_USE_sqlite3_readline = "1"

RECIPE_FLAGS += "sqlite3_extensions"
EXTRA_OECONF_EXTENSIONS = "--disable-dynamic-extensions"
EXTRA_OECONF_EXTENSIONS:USE_sqlite3_extensions = "--enable-dynamic-extensions"
EXTRA_OECONF += "${EXTRA_OECONF_EXTENSIONS}"
DEPENDS:>USE_sqlite3_extensions = " libdl"
# FIXME: -ldl should be passed on to the build system in some way...

SRC_URI = "http://www.sqlite.org/sqlite-${PV}.tar.gz"
S = "${SRCDIR}/sqlite-${PV}"

export config_BUILD_CC = "${BUILD_CC}"
export config_BUILD_CFLAGS = "${BUILD_CFLAGS}"
export config_BUILD_LIBS = "${BUILD_LDFLAGS}"
export config_TARGET_CC = "${CC}"
export config_TARGET_LINK = "${CCLD}"
export config_TARGET_CFLAGS = "${CFLAGS}"
export config_TARGET_LFLAGS = "${LDFLAGS}"

inherit auto-package-utils auto-package-libs

AUTO_PACKAGE_UTILS = "sqlite3"
AUTO_PACKAGE_LIBS = "sqlite3"

FILES_${PN}-libsqlite3-dev = "${includedir}"
RDEPENDS_${PN}-sqlite3 += "libsqlite3"
