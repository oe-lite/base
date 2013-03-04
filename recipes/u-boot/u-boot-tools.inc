# -*- mode:python; -*-
DESCRIPTION = "Das U-Boot bootloader native tools"
HOMEPAGE ?= "http://www.denx.de/wiki/U-Boot"

RECIPE_TYPES = "native sdk"

inherit c make

SRC_URI = "http://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"
S = "${SRCDIR}/u-boot-${PV}"
MIRRORS =. """http://ftp.denx.de/pub/u-boot/ ftp://ftp.denx.de/pub/u-boot/
"""

DEPENDS:sdk = "native:u-boot-tools-bmp-logo"

DO_COMPILE_FIX_SDK_BUILD = ""
DO_COMPILE_FIX_SDK_BUILD:sdk = "do_compile_fix_sdk_build"
do_compile[prefuncs] += "${DO_COMPILE_FIX_SDK_BUILD}"

do_compile_fix_sdk_build() {
    sed 's#$(obj)./bmp_logo $(LOGO_BMP) >$@#${BUILD_SYSROOT}/bin/bmp_logo $(LOGO_BMP) >$@#' -i ${S}/tools/Makefile
}

PARALLEL_MAKE = ""
EXTRA_OEMAKE = 'HOSTCC="${CC}" HOSTSTRIP="${STRIP}" \
    CROSS_COMPILE="${HOST_PREFIX}"'

RECIPE_FLAGS = "u_boot_tools_config"
DEFAULT_USE_u_boot_tools_config = "eNET_config"

do_configure () {
    oe_runmake ${USE_u_boot_tools_config}
}

MAKE_TARGETS = "tools-all"

do_compile[prefuncs] += "do_compile_fix_gdb_include_path"

do_compile_fix_gdb_include_path() {
    sed 's#\(BFD_ROOT_DIR =\).*#\1 ${HOST_SYSROOT}${includedir}#' -i ${S}/config.mk
}

do_compile () {
    oe_runmake ${MAKE_TARGETS}
}

inherit auto-package-utils
U_BOOT_TOOLS = "bmp_logo mkimage envcrc gen_eth_addr img2srec img2brec.sh \
    jtagconsole netconsole setlocalversion"

do_install () {
    install -d ${D}${bindir}
    for tool in ${U_BOOT_TOOLS} ; do
        if [ -f tools/$tool${HOST_EXEEXT} ] ; then
            install -m 0755 tools/$tool${HOST_EXEEXT} \
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
