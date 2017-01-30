DESCRIPTION = "LM sensors: Monitoring tool"
HOMEPAGE = "http://www.lm-sensors.org/"

COMPATIBLE_MACHINES = ".*"

inherit make c auto-package-libs

LICENSE = "GPL-2.0+"
LICENSE_${PN}-libsensors = "LGPL-2.1+"

DEPENDS = "kernel-dev native:flex native:bison libm"

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

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
	fancontrol isadump isaset pwmconfig sensors-detect \
	sensors sensors-conf-convert"
RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
DEPENDS_${PN}-sensors = "libc libsensors"
RDEPENDS_${PN}-sensors = "libc libsensors"
DEPENDS_${PN}-isaset = "libc libsensors"
RDEPENDS_${PN}-isaset = "libc libsensors"
DEPENDS_${PN}-isadump = "libc libsensors"
RDEPENDS_${PN}-isadump = "libc libsensors"
RDEPENDS_${PN}-sensors-conf-convert += "perl"
RDEPENDS_${PN}-sensors-detect += "perl"

PACKAGES =+ "${PN}-config"
FILES_${PN}-config = "${sysconfdir}"
RDEPENDS_${PN}-sensors += "${PN}-config"

AUTO_PACKAGE_LIBS = "sensors"
DEPENDS_${PN}-libsensors += "libc libm"
RDEPENDS_${PN}-libsensors += "libc libm"

FILES_${PN}-dev += "${libdir}/libsensors.so"
FILES_${PN} += "${sysconfdir}"
