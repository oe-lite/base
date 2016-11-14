SUMMARY = "GNU debugger"
HOMEPAGE = "http://www.gnu.org/software/gdb/"
LICENSE = "GPL-2.0+ & GPL-3.0+ & LGPL-2.1+ & LGPL-3.0+"

RECIPE_TYPES = "machine canadian-cross"

GDB_DEPENDS = "host:libc host:libm ${DEPENDS_HOST_OS} host:libexpat host:libreadline"
DEPENDS_HOST_OS = "host:libdl host:libpthread"
DEPENDS_HOST_OS:HOST_LIBC_mingw = ""
DEPENDS = "${GDB_DEPENDS}"

inherit autotools auto-package-utils

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gdb/gdb-${PV}.tar.gz"

EXTRA_OECONF = "--disable-gdbtk --disable-x --disable-werror \
	--disable-multilib --disable-sim \
	--with-system-readline --with-expat \
	--without-lzma --without-python"

RECIPE_FLAGS += "gdb_tui"
DEFAULT_USE_gdb_tui = True
DEFAULT_USE_gdb_tui:HOST_LIBC_mingw = False
GDB_DEPENDS += "${DEPENDS_TUI}"
DEPENDS_TERMCAP = "host:libtermcap"
DEPENDS_TERMCAP:HOST_LIBC_mingw = ""
DEPENDS_CURSES = "host:libncurses"
DEPENDS_TUI = "${DEPENDS_TERMCAP}"
DEPENDS_TUI:USE_gdb_tui = "${DEPENDS_CURSES}"

EXTRA_OECONF_TUI:USE_gdb_tui = "--enable-tui --with-curses"
EXTRA_OECONF_TUI = "--disable-tui --without-curses"
EXTRA_OECONF += "${EXTRA_OECONF_TUI}"

AUTO_PACKAGE_UTILS = "gdb gdbserver gcore"
AUTO_PACKAGE_UTILS:canadian-cross = "gdb"
AUTO_PACKAGE_UTILS_DEPENDS += "host:libc ${DEPENDS_HOST_OS}"
AUTO_PACKAGE_UTILS_RDEPENDS += "host:libc ${DEPENDS_HOST_OS}"
DEPENDS_${PN}-gdb += "host:libreadline host:libm host:libexpat"
RDEPENDS_${PN}-gdb += "host:libreadline host:libm host:libexpat"
DEPENDS_${PN}-gdb:>USE_gdb_tui = " host:libncurses"
RDEPENDS_${PN}-gdb:>USE_gdb_tui = " host:libncurses"
PACKAGES =+ "${PN}-python ${PN}-syscalls ${PN}-system-gdbinit"
FILES_${PN}-python = "${datadir}/gdb/python/"
FILES_${PN}-syscalls = "${datadir}/gdb/syscalls/"
FILES_${PN}-system-gdbinit = "${datadir}/gdb/system-gdbinit/"
RDEPENDS_${PN} += "${PN}-gdb"
