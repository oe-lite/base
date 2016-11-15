DESCRIPTTION = "oFono is a free software project for mobile telephony (GSM/UMTS) applications"
LICENSE = "GPL-2.0"

SRC_URI = "https://www.kernel.org/pub/linux/network/ofono/ofono-${PV}.tar.xz"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig

DEPENDS += "libdl libdbus-1 libglib libutil"
DEPENDS += "mobile-broadband-provider-info-dev"

EXTRA_OECONF += "--disable-udev"

RECIPE_FLAGS += "ofono_dundee"
EXTRA_OECONF += "--disable-dundee"
EXTRA_OECONF:>USE_ofono_dundee = " --enable-dundee"
DEFAULT_USE_ofono_dundee = False

RECIPE_FLAGS += "ofono_qmimodem"
EXTRA_OECONF += "--disable-qmimodem"
EXTRA_OECONF:>USE_ofono_qmimodem = " --enable-qmimodem"
DEFAULT_USE_ofono_qmimodem = True

RECIPE_FLAGS += "ofono_threads"
EXTRA_OECONF += "--disable-threads"
EXTRA_OECONF:>USE_ofono_threads = " --enable-threads"
DEPENDS:>USE_ofono_threads = " libgthread"
DEFAULT_USE_ofono_threads = True

RECIPE_FLAGS += "ofono_test"
EXTRA_OECONF += "--disable-test"
EXTRA_OECONF:>USE_ofono_test = " --enable-test"
DEFAULT_USE_ofono_test = False

RECIPE_FLAGS += "ofono_tools"
EXTRA_OECONF += "--disable-tools"
EXTRA_OECONF:>USE_ofono_tools = " --enable-tools"
DEFAULT_USE_ofono_tools = False


DEPENDS_${PN} += "libc libdbus-1 libdl libglib-2.0"
RDEPENDS_${PN} += "libc libdbus-1 libdl libglib-2.0"
RDEPENDS_${PN} += "mobile-broadband-provider-info"
DEPENDS_${PN}:>USE_ofono_threads = " libgthread"
RDEPENDS_${PN}:>USE_ofono_threads = " libgthread"

inherit sysvinit

RECIPE_FLAGS += "ofono_sysvinit_start ofono_sysvinit_stop"
# dbus must be started, so these must be larger than those of dbus
# (which default to 25)
DEFAULT_USE_ofono_sysvinit_start = "35"
DEFAULT_USE_ofono_sysvinit_stop  = "35"

SRC_URI += "file://init"
do_install_initscript() {
    sysvinit_install_script ${SRCDIR}/init ofono
}
do_install[prefuncs] += "do_install_initscript"
