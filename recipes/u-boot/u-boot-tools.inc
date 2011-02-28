DESCRIPTION = "Das U-Boot bootloader native tools"
LICENSE = "GPL"

BBCLASSEXTEND = "sdk native"

SRC_URI = "ftp://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"
S = "${SRCDIR}/u-boot-${PV}"

PARALLEL_MAKE = ""
EXTRA_OEMAKE = 'HOSTCC="${CC}" HOSTSTRIP="${STRIP}" \
    CROSS_COMPILE="${HOST_PREFIX}"'

RECIPE_OPTIONS = "u_boot_tools_config"
DEFAULT_CONFIG_u_boot_tools_config = "eNET_config"

do_configure () {
    oe_runmake ${RECIPE_OPTION_u_boot_tools_config}
}

MAKE_TARGETS = "tools-all"
MAKE_TARGETS_recipe-native = "tools-all"

do_compile () {
    oe_runmake ${MAKE_TARGETS}
}

inherit auto-package-utils
U_BOOT_TOOLS = "mkimage envcrc gen_eth_addr img2srec img2brec.sh \
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
RPROVIDES_${PN}-env = "util/fw_printenv util/fw_setenv"
