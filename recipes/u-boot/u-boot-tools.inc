DESCRIPTION = "Das U-Boot bootloader native tools"
LICENSE = "GPL"
SECTION = "bootloader"
PROVIDES_${PN}_recipe-native += "u-boot-mkimage${RE}"
RPROVIDES_${PN} += "u-boot-mkimage${RE}"

PR = "r2"

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

U_BOOT_TOOLS ?= "mkimage envcrc gen_eth_addr img2srec img2brec.sh jtagconsole netconsole setlocalversion"

do_install () {
	install -d ${D}${bindir}
	for tool in ${U_BOOT_TOOLS} ; do
		install -m 0755 tools/$tool${HOST_EXEEXT} ${D}${bindir}/$tool${HOST_EXEEXT}
	done
	install -m 0755 tools/env/fw_printenv${HOST_EXEEXT} ${D}${bindir}/fw_printenv${HOST_EXEEXT}
	ln -s fw_printenv ${D}${bindir}/fw_setenv${HOST_EXEEXT}
}

PACKAGES =+ "${PN}-env"

FILES_${PN}-env = "${bindir}/fw_*env"
