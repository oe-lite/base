DESCRIPTION = "LTTng Userspace Tracer (UST)"
SECTION = "devel"
PRIORITY = "optional"
LICENSE = "GPLv2 and LGPLv2.1"

inherit sysvinit

RECIPE_OPTIONS = "ust_sysvinit_start ust_sysvinit_stop ust_basedir"

SYSVINIT_SCRIPT_ust = "ustd"
DEFAULT_CONFIG_ust_sysvinit_start		= "99"
DEFAULT_CONFIG_ust_sysvinit_stop		= "0"

DEFAULT_CONFIG_ust_basedir			= "/tmp/ust"

SRC_URI = "http://lttng.org/files/ust/releases/ust-${PV}.tar.gz \
	file://ustd.init"

inherit autotools

UST_LIB_DEPENDS = "\
	liburcu \
	${TARGET_ARCH}/sysroot-libpthread \
	${TARGET_ARCH}/sysroot-libdl \
"

# Recipe build dependencies
DEPENDS =+ "${UST_LIB_DEPENDS}"

# Package build dependencies
PROVIDES_${PN}-dev += "libust"
DEPENDS_${PN}-dev = "${PN} ${UST_LIB_DEPENDS}"

# Package run-time dependencies
RPROVIDES_${PN} += "libust"
RDEPENDS_${PN} = "${UST_LIB_DEPENDS} cmd/which cmd/tee"
RDEPENDS_${PN}-dev = "${PN} userspace-rcu-dev"

do_compile_append () {
	sed -e 's|^#!/bin/bash$|#!/bin/sh|' \
	    -e 's/^function \(.*() *{\)$/\1/' \
	    -e 's|^\(BASE_TRACE_DIR\)=.*|\1="${RECIPE_OPTION_ust_basedir}"|' \
	    -e 's/\(.*\)="$(<\(.*\))"/\1=`cat \2`/' \
	    -e 's/^\(DATESTRING\)=.*/\1="$(date +%Y%m%d%H%M%S)"/' \
	    -i ${S}/usttrace
	sed -e 's|^\(TRACEDIR\)=.*|\1="${RECIPE_OPTION_ust_basedir}"|' \
	    -i ${SRCDIR}/ustd.init
}

do_install_append () {
	sysvinit_install_script ${SRCDIR}/ustd.init ustd
}

# Need the .so symlinks for preload to work
FILES_${PN} += "${libdir}/libust*.so"
