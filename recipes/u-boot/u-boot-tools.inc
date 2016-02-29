# -*- mode:python; -*-
DESCRIPTION = "Das U-Boot bootloader native tools"
HOMEPAGE ?= "http://www.denx.de/wiki/U-Boot"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make

SRC_URI = "http://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"
S = "${SRCDIR}/u-boot-${PV}"
MIRRORS =. """http://ftp.denx.de/pub/u-boot/ ftp://ftp.denx.de/pub/u-boot/
"""

EXTRA_OEMAKE = "NO_SDL=1"
EXTRA_OEMAKE_CROSS = 'CROSS_COMPILE="${HOST_PREFIX}" LDFLAGS="${LDFLAGS}"'
EXTRA_OEMAKE:>machine = " ${EXTRA_OEMAKE_CROSS}"
EXTRA_OEMAKE:>native = ' HOSTCC="${BUILD_CC}" HOSTLDFLAGS="${BUILD_LDFLAGS}"'
EXTRA_OEMAKE:>sdk = " ${EXTRA_OEMAKE_CROSS}"

RECIPE_FLAGS = "u_boot_tools_config"
DEFAULT_USE_u_boot_tools_config = "defconfig"

do_configure () {
    oe_runmake ${USE_u_boot_tools_config}
}

MAKE_TARGETS:machine = "cross_tools env"
MAKE_TARGETS:native = "tools-all"
MAKE_TARGETS:sdk = "cross_tools"

do_compile[prefuncs] += "do_compile_fix_gdb_include_path"

do_compile_fix_gdb_include_path() {
    sed 's#\(BFD_ROOT_DIR =\).*#\1 ${HOST_SYSROOT}${includedir}#' -i ${S}/tools/gdb/Makefile
}

do_compile () {
    oe_runmake ${MAKE_TARGETS}
}

inherit auto-package-utils
U_BOOT_TOOLS = "bmp_logo mkimage envcrc gen_eth_addr img2srec img2brec.sh \
    jtagconsole netconsole setlocalversion"

GDB_TOOLS = "gdbcont gdbsend"

do_install () {
    install -d ${D}${bindir}
    for tool in ${U_BOOT_TOOLS} ; do
        if [ -f tools/$tool${HOST_EXEEXT} ] ; then
            install -m 0755 tools/$tool${HOST_EXEEXT} \
                ${D}${bindir}/$tool${HOST_EXEEXT}
        fi
    done

    for tool in ${GDB_TOOLS} ; do
        if [ -f tools/gdb/$tool${HOST_EXEEXT} ] ; then
            install -m 0755 tools/gdb/$tool${HOST_EXEEXT} \
                ${D}${bindir}/$tool${HOST_EXEEXT}
        fi
    done

    if [ -f tools/env/fw_printenv${HOST_EXEEXT} ] ; then
        install -m 0755 tools/env/fw_printenv${HOST_EXEEXT} \
            ${D}${bindir}/fw_printenv${HOST_EXEEXT}
    fi
    ln -s fw_printenv${HOST_EXEEXT} ${D}${bindir}/fw_setenv${HOST_EXEEXT}
}

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "${U_BOOT_TOOLS}"

PACKAGES =+ "${PN}-env"
FILES_${PN}-env = "${bindir}/fw_*env"
PROVIDES_${PN}-env = "util/fw_printenv util/fw_setenv"

DEPENDS_${PN}-mkimage += "dtc"
RDEPENDS_${PN}-mkimage += "dtc"

PACKAGES:<native =+ "${PN}-gdb "
FILES_${PN}-gdb = "${bindir}/gdb*"
