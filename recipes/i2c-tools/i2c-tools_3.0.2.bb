DESCRIPTION = "Set of i2c tools for linux"
SECTION = "base"
LICENSE = "GPLv2"

SRC_URI = "http://dl.lm-sensors.org/i2c-tools/releases/i2c-tools-${PV}.tar.bz2 \
           file://Module.mk \
          "

inherit autotools

do_compile_prepend() {
        cp ${WORKDIR}/Module.mk ${S}/eepromer/
        sed -i 's#/usr/local#/usr#' Makefile
        sed -i 's#CC\t:= gcc#CC\t:= ${CC}#' Makefile
        echo "include eepromer/Module.mk" >> Makefile
}

do_install_append() {
        install -d ${D}{$includedir}/linux
        install -m 0644 include/linux/i2c-dev.h ${D}${includedir}/linux/i2c-dev-user.h
	rm -f ${D}${includedir}/linux/i2c-dev.h
}
