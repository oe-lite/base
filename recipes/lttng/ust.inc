# -*- mode:python; -*-
DESCRIPTION = "LTTng Userspace Tracer (UST)"
LICENSE = "GPLv2 and LGPLv2.1"

RECIPE_TYPES = "machine"

inherit sysvinit autotools-autoreconf

SRC_URI = "http://lttng.org/files/ust/releases/ust-${PV}.tar.gz"
SRC_URI += "file://ust-consumerd.init"

RECIPE_FLAGS = "ust_sysvinit_start ust_sysvinit_stop ust_basedir"

SYSVINIT_SCRIPT_ust = "ust-consumerd"
DEFAULT_USE_ust_sysvinit_start		= "99"
DEFAULT_USE_ust_sysvinit_stop		= "0"

DEFAULT_USE_ust_basedir			= "/tmp/ust"

UST_LIB_DEPENDS = "liburcu libpthread libdl librt"

# Recipe build dependencies
DEPENDS =+ "${UST_LIB_DEPENDS}"

do_compile[postfuncs] += "do_compile_sed"
do_compile_sed () {
	sed -e 's|^#!/bin/bash$|#!/bin/sh|' \
	    -e 's/^function \(.*() *{\)$/\1/' \
	    -e 's|^\(BASE_TRACE_DIR\)=.*|\1="${USE_ust_basedir}"|' \
	    -e 's/\(.*\)="$(<\(.*\))"/\1=`cat \2`/' \
	    -e 's/^\(DATESTRING\)=.*/\1="$(date +%Y%m%d%H%M%S)"/' \
	    -i ${S}/usttrace
	sed -e 's|^\(TRACEDIR\)=.*|\1="${USE_ust_basedir}"|' \
	    -i ${SRCDIR}/ust-consumerd.init
}

do_install[postfuncs] =+ "do_install_initscript"
do_install_initscript () {
	sysvinit_install_script ${SRCDIR}/ust-consumerd.init ust-consumerd
}

# Package dependencies
RDEPENDS_${PN} += "${PN}-ust-consumerd"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "ust ustctl ustconsumer ustfork ustinstr-malloc"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_DEV_RDEPENDS = "${PN}-dev_${PV}"
FILES_${PN}-libust = "${libdir}/libust${SOLIBSDEV}"
FILES_${PN}-libustfork = "${libdir}/libustfork${SOLIBSDEV}"
FILES_${PN}-libustinstr-malloc = "${libdir}/libustinstr-malloc${SOLIBSDEV}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "ustctl ust-consumerd usttrace"
RDEPENDS_${PN}-ustctl = "libustctl liburcu libpthread libc"
RDEPENDS_${PN}-ust-consumerd = "libustconsumer liburcu libpthread libc"

DEPENDS_${PN}-libust += "${UST_LIB_DEPENDS}"
