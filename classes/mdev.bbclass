#
# OE-lite class for recipes providing content for mdev.conf file
#

require conf/mdev.conf

RECIPE_OPTIONS_append += "mdev"

MDEV_DEFAULT_RDEPENDS = ""
MDEV_DEFAULT_RDEPENDS_RECIPE_OPTION_mdev = "mdev"
RDEPENDS_${PN}_append += "${MDEV_DEFAULT_RDEPENDS}"

MDEV_CONF_FILES ?= "${SRCDIR}/mdev.conf"

addtask install_mdev after do_install before do_install_fixup
do_install_mdev[dirs] = "${D}"

do_install_mdev () {
	i=0
        test -z "${RECIPE_OPTION_mdev}" -o "${RECIPE_OPTION_mdev}"="0" || return
	for f in ${MDEV_CONF_FILES} ; do
		# only create mdevdir when needed, and let it fail silently when
		# called more than once
		mkdir -p ./${mdevdir}
		let i=$i+1
		cp $f ./${mdevdir}/${PN}.$i
	done
}
