DESCRIPTION = "Das U-Boot bootloader native tools"
LICENSE = "GPL"

BBCLASSEXTEND = "sdk native"

SRC_URI = "ftp://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"
S = "${SRCDIR}/u-boot-${PV}"

PARALLEL_MAKE = ""
#EXTRA_OEMAKE = 'HOSTCC="${CC}" HOSTCFLAGS="${CFLAGS}" HOSTSTRIP="${STRIP}" CROSS_COMPILE= CFLAGS="${CFLAGS}"'
EXTRA_OEMAKE = 'HOSTCC="${CC}" HOSTCFLAGS="${CFLAGS}" HOSTSTRIP="${STRIP}"'

RECIPE_OPTIONS = "u_boot_tools_config"
DEFAULT_CONFIG_u_boot_tools_config = "smdk2410_config"

do_configure () {
    oe_runmake ${RECIPE_OPTION_u_boot_tools_config}
}

MAKE_TARGETS = "tools env"
MAKE_TARGETS_recipe-native = "tools"

do_compile () {
    oe_runmake ${MAKE_TARGETS}
}

U_BOOT_TOOLS ?= "mkimage${HOST_EXEEXT} envcrc${HOST_EXEEXT} gen_eth_addr${HOST_EXEEXT} img2srec${HOST_EXEEXT} img2brec.sh${HOST_EXEEXT} jtagconsole${HOST_EXEEXT} netconsole${HOST_EXEEXT} setlocalversion${HOST_EXEEXT}"

do_install () {
    install -d ${D}${bindir}
    for tool in ${U_BOOT_TOOLS} ; do
	if [ -f tools/$tool ] ; then
	    install -m 0755 tools/$tool \
		${D}${bindir}/$tool
	fi
    done
    if [ -f tools/env/fw_printenv${HOST_EXEEXT} ] ; then
	install -m 0755 tools/env/fw_printenv${HOST_EXEEXT} \
	    ${D}${bindir}/fw_printenv${HOST_EXEEXT}
    fi
    ln -s fw_printenv${HOST_EXEEXT} ${D}${bindir}/fw_setenv${HOST_EXEEXT}
}

PACKAGES =+ "${PN}-env"

FILES_${PN}-env = "${bindir}/fw_*env"

PROVIDES_${PN}_recipe-native += "${PN} u-boot-mkimage${RE}"
RPROVIDES_${PN} = "${PN} u-boot-mkimage${RE}"
