DESCRIPTION = "Set of i2c tools for linux"

inherit autotools auto-package-utils

SRC_URI = "http://dl.lm-sensors.org/i2c-tools/releases/i2c-tools-${PV}.tar.bz2"
SRC_URI += "file://Module.mk"

do_configure[postfuncs] += "do_configure_eepromer_makefile"
do_configure_eepromer_makefile() {
	cp ${SRCDIR}/Module.mk ${S}/eepromer/
	sed -i 's#/usr/local#/usr#' Makefile
	sed -i 's#CC\t:= gcc#CC\t:= ${CC}#' Makefile
	echo "include eepromer/Module.mk" >> Makefile
}

do_install[postfuncs] += "do_install_extra_files"
do_install_extra_files() {
	install -d ${D}${includedir}/linux
	install -m 0644 include/linux/i2c-dev.h \
		${D}${includedir}/linux/i2c-dev-user.h
	rm -f ${D}${includedir}/linux/i2c-dev.h
}

AUTO_PACKAGE_UTILS = "ddcmon decode-dimms decode-edid decode-vaio \
	eeprog eeprom eepromer i2cdetect i2cdump i2cget i2cset \
	i2c-stub-from-dump"

# The i2c-tools package is used to pull in all provided util features
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PROVIDES}"
