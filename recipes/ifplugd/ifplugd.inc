# -*- mode:python; -*-
DESCRIPTION = "ifplugd is a Linux daemon which will automatically configure \
	your ethernet device when a cable is plugged in and automatically \
	unconfigure it if the cable is pulled."
HOMEPAGE = "http://0pointer.de/lennart/projects/ifplugd/"

RECIPE_TYPES = "machine"

inherit c++ autotools pkgconfig sysvinit

SRC_URI = "http://0pointer.de/lennart/projects/ifplugd/ifplugd-${PV}.tar.gz"

DEPENDS = "libdaemon"

EXTRA_OECONF = "--disable-lynx"

RECIPE_FLAGS += "ifplugd_sysvinit_start ifplugd_sysvinit_stop"
SYSVINIT_SCRIPT_ifplugd = "ifplugd"
DEFAULT_USE_ifplugd_sysinit_start = "25"
DEFAULT_USE_ifplugd_sysinit_stop  = "20"

RDEPENDS_${PN} = "libdaemon"
