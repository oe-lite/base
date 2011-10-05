# -*- mode:python; -*-
DESCRIPTION = "LTTng Userspace Tracer (UST)"
LICENSE = "GPLv2 and LGPLv2.1"

RECIPE_TYPES = "machine"

inherit sysvinit autotools-autoreconf auto-package-libs

SRC_URI = "http://lttng.org/files/ust/releases/ust-${PV}.tar.gz"
SRC_URI += "file://ustd.init"

RECIPE_FLAGS = "ust_sysvinit_start ust_sysvinit_stop ust_basedir"

SYSVINIT_SCRIPT_ust = "ustd"
DEFAULT_USE_ust_sysvinit_start		= "99"
DEFAULT_USE_ust_sysvinit_stop		= "0"

DEFAULT_USE_ust_basedir			= "/tmp/ust"

UST_LIB_DEPENDS = "liburcu libpthread libdl librt"

AUTO_PACKAGE_LIBS = "ust"

# Recipe build dependencies
DEPENDS =+ "${UST_LIB_DEPENDS}"

# Package dependencies
DEPENDS_${PN}-libust += "${UST_LIB_DEPENDS}"
RDEPENDS_${PN} += "libust util/which util/tee"

do_compile[postfuncs] += "do_compile_sed"
do_compile_sed () {
	sed -e 's|^#!/bin/bash$|#!/bin/sh|' \
	    -e 's/^function \(.*() *{\)$/\1/' \
	    -e 's|^\(BASE_TRACE_DIR\)=.*|\1="${USE_ust_basedir}"|' \
	    -e 's/\(.*\)="$(<\(.*\))"/\1=`cat \2`/' \
	    -e 's/^\(DATESTRING\)=.*/\1="$(date +%Y%m%d%H%M%S)"/' \
	    -i ${S}/usttrace
	sed -e 's|^\(TRACEDIR\)=.*|\1="${USE_ust_basedir}"|' \
	    -i ${SRCDIR}/ustd.init
}

do_install[postfuncs] += "do_install_initscript"
do_install_initscript () {
	sysvinit_install_script ${SRCDIR}/ustd.init ustd
}

FILES_${PN}-libust-dev += "${FILES_${PN}-dev}"
# Need the .so symlinks for preload to work
FILES_${PN}-libust += "${libdir}/libust*.so* ${bindir} ${"
