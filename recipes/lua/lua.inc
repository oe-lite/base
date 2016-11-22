DESCRIPTION = "A powerful, fast, lightweight, embeddable scripting language"

inherit c make auto-package-utils

SRC_URI = "http://www.lua.org/ftp/lua-${PV}.tar.gz"

DEPENDS += "libm ${DEPENDS_LIBC} libreadline"
DEPENDS_LIBC = "libdl libncurses"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

PLAT = "linux"
PLAT:HOST_LIBC_mingw = "mingw"
PLAT:HOST_KERNEL_darwin = "macosx"

do_compile () {
	cd src && make ${PLAT} CC="${CC}" AR="${AR} rcu"
}

do_install[prefuncs] += "do_install_fix_dirs"
do_install_fix_dirs () {
	sed -i -e 's/\(INSTALL_TOP= \).*/\1\$\{DESTDIR\}\/usr/' ${S}/Makefile
}

EXTRA_OEMAKE_INSTALL += "EXEEXT=${HOST_EXEEXT}"
do_install[postfuncs] += "do_install_fix_mandir"
do_install_fix_mandir () {
	mkdir -p ${D}${mandir}
	mv ${D}/usr/man/* ${D}${mandir}
}

AUTO_PACKAGE_UTILS = "lua luac"

RDEPENDS_LUA = "libm ${DEPENDS_LIBC} libreadline libc"
RDEPENDS_${PN}-lua = "${RDEPENDS_LUA}"
RDEPENDS_${PN}-luac = "${RDEPENDS_LUA}"
