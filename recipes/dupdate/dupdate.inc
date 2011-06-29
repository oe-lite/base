DESCRIPTION = "Update daemon watching a dir for firmware updates"
LICENSE = "GPLv2"

RECIPE_OPTIONS = "\
	dupdate_backend \
	dupdate_imagemode \
	dupdate_sysvinit_start \
	dupdate_sysvinit_stop \
"

DEFAULT_CONFIG_dupdate_backend = "mtd"
DEFAULT_CONFIG_dupdate_imagemode = "dual"

inherit sysvinit
DEFAULT_CONFIG_dupdate_sysvinit_start = "60"
RDEPENDS_${PN}_append_RECIPE_OPTION_sysvinit += "start-stop-daemon"

SRC_URI = "git://git.doredevelopment.dk/dupdate.git;protocol=git"
S = "${SRCDIR}/git"

inherit autotools

EXTRA_OECONF = "--with-backend=${RECIPE_OPTION_dupdate_backend}"
EXTRA_OECONF += "--with-imagemode=${RECIPE_OPTION_dupdate_imagemode}"

do_install_append_RECIPE_OPTION_sysvinit () {
    sysvinit_install_script ${S}/src/dupdate.sh dupdate
}
