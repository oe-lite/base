DESCRIPTION = "Set of i2c tools for linux"
SECTION = "base"
LICENSE = "GPLv2"

inherit autotools auto-package-utils

SRC_URI = "http://dl.lm-sensors.org/i2c-tools/releases/i2c-tools-${PV}.tar.bz2"
SRC_URI += "file://Module.mk"

do_compile_prepend() {
    cp ${SRCDIR}/Module.mk ${S}/eepromer/
    sed -i 's#/usr/local#/usr#' Makefile
    sed -i 's#CC\t:= gcc#CC\t:= ${CC}#' Makefile
    echo "include eepromer/Module.mk" >> Makefile
}

do_install_append() {
    install -d ${D}${includedir}/linux
    install -m 0644 include/linux/i2c-dev.h ${D}${includedir}/linux/i2c-dev-user.h
	rm -f ${D}${includedir}/linux/i2c-dev.h
}

AUTO_PACKAGE_UTILS = "ddcmon decode-dimms decode-edid decode-vaio \
    eeprog eeprom eepromer i2cdetect i2cdump i2cget i2cset i2c-stub-from-dump"

# The i2c-tools package is used to pull in all provided util features
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_RPROVIDES}"
