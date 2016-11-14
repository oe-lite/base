# -*- mode:python; -*-
DESCRIPTION = "An Embeddable SQL Database Engine"
HOMEPAGE = "http://www.sqlite.org"
LICENSE = "Public Domain"

RECIPE_TYPES = "native machine"

addhook sqlite3_file_version_mangle to post_recipe_parse first
def sqlite3_file_version_mangle(d):
    pv = map(int, d.get("PV").split("."))
    while len(pv) < 4:
        pv.append(0)
    pv_mangled = "%d%02d%02d%02d"%tuple(pv)
    d.set("PV_MANGLED", pv_mangled)

SRC_URI = "http://www.sqlite.org/2016/sqlite-autoconf-${PV_MANGLED}.tar.gz"
S = "${SRCDIR}/sqlite-autoconf-${PV_MANGLED}"

inherit autotools pkgconfig

RECIPE_FLAGS += "sqlite3_largefile"
EXTRA_OECONF_LARGEFILE = "--disable-largefile"
EXTRA_OECONF_LARGEFILE:USE_sqlite3_largefile = "--enable-largefile"
EXTRA_OECONF += "${EXTRA_OECONF_LARGEFILE}"

RECIPE_FLAGS += "sqlite3_threadsafe"
EXTRA_OECONF_THREADSAFE = "--disable-threadsafe"
EXTRA_OECONF_THREADSAFE:USE_sqlite3_threadsafe = "--enable-threadsafe"
EXTRA_OECONF += "${EXTRA_OECONF_THREADSAFE}"
DEPENDS_PTHREAD = "libpthread"
DEPENDS_PTHREAD:HOST_LIBC_mingw = ""
DEPENDS:>USE_sqlite3_threadsafe = " ${DEPENDS_PTHREAD}"
DEFAULT_USE_sqlite3_threadsafe = True

RECIPE_FLAGS += "sqlite3_readline"
EXTRA_OECONF_READLINE = "--disable-readline"
EXTRA_OECONF_READLINE:USE_sqlite3_readline = "--enable-readline"
EXTRA_OECONF += "${EXTRA_OECONF_READLINE}"
DEPENDS:>USE_sqlite3_readline = " libreadline"
DEFAULT_USE_sqlite3_readline = True

RECIPE_FLAGS += "sqlite3_extensions"
EXTRA_OECONF_EXTENSIONS = "--disable-dynamic-extensions"
EXTRA_OECONF_EXTENSIONS:USE_sqlite3_extensions = "--enable-dynamic-extensions"
EXTRA_OECONF += "${EXTRA_OECONF_EXTENSIONS}"
DEPENDS:>USE_sqlite3_extensions = " libdl"
# FIXME: -ldl should be passed on to the build system in some way...

export config_BUILD_CC = "${BUILD_CC}"
export config_BUILD_CFLAGS = "${BUILD_CFLAGS}"
export config_BUILD_LIBS = "${BUILD_LDFLAGS}"
export config_TARGET_CC = "${CC}"
export config_TARGET_LINK = "${CCLD}"
export config_TARGET_CFLAGS = "${CFLAGS}"
export config_TARGET_LFLAGS = "${LDFLAGS}"

inherit auto-package-utils auto-package-libs

AUTO_PACKAGE_UTILS = "sqlite3"
AUTO_PACKAGE_UTILS_DEPENDS = "libsqlite3 libpthread libc"
AUTO_PACKAGE_UTILS_RDEPENDS = "libsqlite3 libpthread libc"
AUTO_PACKAGE_UTILS_DEPENDS:>USE_sqlite3_readline = " libreadline"
AUTO_PACKAGE_UTILS_RDEPENDS:>USE_sqlite3_readline = " libreadline"
AUTO_PACKAGE_UTILS_DEPENDS:>USE_sqlite3_extensions = " libdl"
AUTO_PACKAGE_UTILS_RDEPENDS:>USE_sqlite3_extensions = " libdl"
AUTO_PACKAGE_LIBS = "sqlite3"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "libpthread libc"
AUTO_PACKAGE_LIBS_RDEPENDS = "libpthread libc"
AUTO_PACKAGE_LIBS_DEPENDS:>USE_sqlite3_extensions = " libdl"
AUTO_PACKAGE_LIBS_RDEPENDS:>USE_sqlite3_extensions = " libdl"

FILES_${PN}-libsqlite3-dev = "${includedir}"
