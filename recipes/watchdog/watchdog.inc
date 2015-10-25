SUMMARY = "Software watchdog"
DESCRIPTION = "Watchdog is a daemon that checks if your system is still \
working. If programs in user space are not longer executed \
it will reboot the system."
HOMEPAGE = "http://watchdog.sourceforge.net/"
BUGTRACKER = "http://sourceforge.net/tracker/?group_id=172030&atid=860194"

LICENSE = "GPL-2.0+"

COMPATIBLE_HOST_ARCHS = ".*linux"

require conf/fetch/sourceforge.conf

SRC_URI = "${SOURCEFORGE_MIRROR}/watchdog/watchdog-${PV}.tar.gz \
           file://fixsepbuild.patch \
	   file://fix-ping-failure.patch \
	   file://watchdog.init"

inherit autotools

EXTRA_OECONF += " --disable-nfs"

DEPENDS_${PN} = "libc"
RDEPENDS_${PN} = "libc watchdog-conf"

PACKAGES =+ "${PN}-config"

FILES_${PN}-config += "${sysconfdir}/watchdog.conf"

PROVIDES_${PN}-config = "watchdog-conf"

do_install[postfuncs] += "do_install_extra_files"
do_install_extra_files() {
	install -D ${SRCDIR}/watchdog.init ${D}/${sysconfdir}/init.d/watchdog-daemon
}

inherit sysvinit
RECIPE_FLAGS += "watchdog_sysvinit_start watchdog_sysvinit_stop"
SYSVINIT_SCRIPT_watchdog = "watchdog-daemon"
DEFAULT_USE_watchdog_sysvinit_start = "99"
DEFAULT_USE_watchdog_sysvinit_stop  = "99"
