DESCRIPTION = "Update daemon watching a dir for firmware updates"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit sysvinit
RECIPE_FLAGS += "dupdate_sysvinit_start dupdate_sysvinit_stop"
DEFAULT_USE_dupdate_sysvinit_start = "60"
RDEPENDS_${PN}:>USE_sysvinit += "util/start-stop-daemon"

SRC_URI = "git://oe-lite.org/dupdate.git;protocol=git;${SRC_REV}"
S = "${SRCDIR}/dupdate"

inherit autotools

RECIPE_FLAGS += "dupdate_exefile dupdate_args"
include conf/dupdate.conf
DEFAULT_USE_dupdate_exefile ?= "run_update.sh"
DEFAULT_USE_dupdate_args ?= "$DIR -x $EXEFILE -l"

do_configure[postfuncs] =+ "do_configure_EXEFILE"
do_configure_EXEFILE() {
    sed 's/^EXEFILE.*/EXEFILE="${USE_dupdate_exefile}"/' -i ${S}/src/dupdate.sh
}

do_configure[postfuncs] =+ "do_configure_ARGS"
do_configure_ARGS() {
    sed 's/^ARGS.*/ARGS="${USE_dupdate_args}"/' -i ${S}/src/dupdate.sh
}

INSTALL_SYSVINIT_POSTFUNC = ""
INSTALL_SYSVINIT_POSTFUNC:USE_sysvinit = "do_install_sysvinit_dupdate"
do_install[postfuncs] =+ "${INSTALL_SYSVINIT_POSTFUNC}"
do_install_sysvinit_dupdate () {
    sysvinit_install_script ${S}/src/dupdate.sh dupdate
}

inherit splashutils-progress
RECIPE_FLAGS += "dupdate_splashutils_progress dupdate_splashutils_msg"
SPLASHUTILS_INITSCRIPTS = ""
SPLASHUTILS_INITSCRIPTS:USE_sysvinit = "dupdate"
DEFAULT_USE_dupdate_splashutils_msg = "\"Starting Dupdate Daemon\""

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
