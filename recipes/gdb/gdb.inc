SUMMARY = "GNU debugger"
HOMEPAGE = "http://www.gnu.org/software/gdb/"
LICENSE = "GPLv2 & GPLv3 & LGPLv2 & LGPLv3"

RECIPE_TYPES = "machine canadian-cross"

GDB_DEPENDS = "host:libexpat host:libtermcap \
	host:libreadline host:libdl host:libm host:libc"
DEPENDS = "${GDB_DEPENDS}"
RDEPENDS_${PN} = "${GDB_DEPENDS}"

inherit autotools auto-package-utils

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gdb/gdb-${PV}.tar.gz"
S = "${SRCDIR}/${PN}-${PV}"

EXTRA_OEMAKE = "'SUBDIRS=gdb'"

EXTRA_OECONF = "--disable-gdbtk --disable-tui --disable-x --disable-werror \
	--with-curses --disable-multilib --with-system-readline --disable-sim \
        --without-lzma --without-python \
        --program-prefix='' --with-expat"

AUTO_PACKAGE_UTILS = "gdb gdbserver gcore"
AUTO_PACKAGE_UTILS:canadian-cross = "gdb"
AUTO_PACKAGE_UTILS_DEPENDS += "host:libc host:libdl"
AUTO_PACKAGE_UTILS_RDEPENDS += "host:libc host:libdl"
RDEPENDS_${PN}-gdb += "host:libreadline host:libncurses host:libm host:libexpat"

PACKAGES =+ "${PN}-python ${PN}-syscalls ${PN}-system-gdbinit"
FILES_${PN}-python = "${datadir}/gdb/python/"
FILES_${PN}-syscalls = "${datadir}/gdb/syscalls/"
FILES_${PN}-system-gdbinit = "${datadir}/gdb/system-gdbinit/"
