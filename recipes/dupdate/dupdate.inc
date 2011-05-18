DESCRIPTION = "Update daemon watching a dir for firmware updates"
LICENSE = "GPLv2"
SECTION = "console/utils"
RDEPENDS_${PN} = "mtd-utils-core mtd-utils-ubi"

PR = "r10"

RECIPE_OPTIONS = "\
	dupdate_backend \
	dupdate_sysvinit_start \
	dupdate_sysvinit_stop \
"

DEFAULT_CONFIG_dupdate_backend = "mtd"

inherit sysvinit
DEFAULT_CONFIG_dupdate_sysvinit_start = "60"
DEFAULT_CONFIG_dupdate_sysvinit_stop = "0"
RDEPENDS_${PN}_append_RECIPE_OPTION_sysvinit += "start-stop-daemon"

SRC_URI = "git://git.doredevelopment.dk/dupdate.git;protocol=git"
S = "${SRCDIR}/git"

inherit autotools

EXTRA_OECONF = "--with-backend=${RECIPE_OPTION_dupdate_backend}"

do_install_append_RECIPE_OPTION_sysvinit () {
	install -d ${D}/${sysconfdir}/init.d/
	install -p -m 755 ${S}/src/dupdate.sh ${D}/${sysconfdir}/init.d/dupdate
}
