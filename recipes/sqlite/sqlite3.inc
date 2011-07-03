# -*- mode:python; -*-
DESCRIPTION = "An Embeddable SQL Database Engine"
HOMEPAGE = "http://www.sqlite.org"
LICENSE = "PD"

RECIPE_TYPES = "machine"

inherit autotools pkgconfig

DEPENDS = "libreadline libncurses libpthread"

SRC_URI = "http://www.sqlite.org/sqlite-${PV}.tar.gz"
S = "${SRCDIR}/sqlite-${PV}"

EXTRA_OECONF = "--disable-tcl --enable-shared --enable-threadsafe"

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
