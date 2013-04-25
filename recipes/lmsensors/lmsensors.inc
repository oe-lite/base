DESCRIPTION = "LM sensors: Monitoring tool"
HOMEPAGE = "http://www.lm-sensors.org/"

COMPATIBLE_MACHINES = ".*"

inherit make c

DEPENDS = "kernel-dev native:flex native:bison libm"

RDEPENDS_${PN} = "libm"

SRC_URI = "http://dl.lm-sensors.org/lm-sensors/releases/lm_sensors-${PV}.tar.bz2"
S = "${SRCDIR}/lm_sensors-${PV}"

do_compile[prefuncs] += "do_compile_remove_prefix"
do_compile_remove_prefix () {
	sed -i -e 's/\(PREFIX :=\).*/\1\${prefix}/' Makefile
	sed -i -e 's/\(CC :=\).*/\1\"${CC}"/' Makefile
}

do_compile() {
	export PREFIX=${prefix}
        oe_runmake \
		LINUX=${HOST_SYSROOT}${kernelsrcdir} \
		TARGET_ARCH=${TARGET_ARCH} \
		user PROG_EXTRA=sensors
}

do_install() {
        oe_runmake user_install DESTDIR=${D}

        install -d ${D}${mandir}
        rm -rf ${D}${mandir}/*
        mv ${D}/usr/man/ ${D}${mandir}
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN} ${PN}-dev ${PN}-locale"
inherit auto-package-utils
AUTO_PACKAGE_UTILS = "fancontrol isadump isaset pwmconfig sensors-detect sensors sensors-conf-convert"
RDEPENDS_${PN} += "${PN}-sensors"

FILES_${PN} += "${libdir}/libsensors.so"
