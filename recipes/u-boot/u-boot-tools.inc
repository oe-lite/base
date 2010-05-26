DESCRIPTION = "Das U-Boot bootloader native tools"
LICENSE = "GPL"
SECTION = "bootloader"
PROVIDES_${PN}_recipe-native += "u-boot-mkimage${RE}"
RPROVIDES_${PN} += "u-boot-mkimage${RE}"

PR = "r1"

SRC_URI = "ftp://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"

S = "${WORKDIR}/u-boot-${PV}"

PARALLEL_MAKE = ""
EXTRA_OEMAKE = 'HOSTCC="${CC} ${CFLAGS}" HOSTSTRIP="${STRIP}"'

do_compile () {
 	oe_runmake smdk2410_config
        oe_runmake tools
}

U_BOOT_TOOLS ?= "mkimage"

do_install () {
	install -d ${D}${bindir}
	for tool in "${U_BOOT_TOOLS}" ; do
		install -m 0755 tools/$tool ${D}${bindir}/$tool
	done
}

BBCLASSEXTEND = "sdk"