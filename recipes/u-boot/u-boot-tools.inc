DESCRIPTION = "Das U-Boot bootloader native tools"
LICENSE = "GPL"
SECTION = "bootloader"
PROVIDES_${PN}_recipe-native += "u-boot-mkimage${RE}"
RPROVIDES_${PN} += "u-boot-mkimage${RE}"

BBCLASSEXTEND = "sdk native"

RECIPE_OPTIONS = "u_boot_tools_config"
DEFAULT_CONFIG_u_boot_tools_config = "smdk2410_config"

SRC_URI = "ftp://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"

S = "${WORKDIR}/u-boot-${PV}"

PARALLEL_MAKE = ""
EXTRA_OEMAKE = 'HOSTCC="${CC} ${CFLAGS}" HOSTSTRIP="${STRIP}"'

do_compile () {
 	oe_runmake CROSS_COMPILE=${HOST_PREFIX} ${RECIPE_OPTION_u_boot_tools_config}
        oe_runmake CROSS_COMPILE=${HOST_PREFIX} tools env
}

U_BOOT_TOOLS ?= "mkimage${HOST_EXEEXT} envcrc${HOST_EXEEXT} gen_eth_addr${HOST_EXEEXT} img2srec${HOST_EXEEXT} img2brec.sh${HOST_EXEEXT} jtagconsole${HOST_EXEEXT} netconsole${HOST_EXEEXT} setlocalversion${HOST_EXEEXT}"

do_install () {
	install -d ${D}${bindir}
	for tool in ${U_BOOT_TOOLS} ; do
		if -f $tool ; then
			install -m 0755 tools/$tool \
				${D}${bindir}/$tool
		fi
	done
	install -m 0755 tools/env/fw_printenv${HOST_EXEEXT} \
		${D}${bindir}/fw_printenv${HOST_EXEEXT}
	ln -s fw_printenv${HOST_EXEEXT} ${D}${bindir}/fw_setenv${HOST_EXEEXT}
}

PACKAGES =+ "${PN}-env"

FILES_${PN}-env = "${bindir}/fw_*env"
