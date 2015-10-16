DESCRIPTION = "tmux terminal multiplexer"
HOMEPAGE = "https://tmux.github.io/"
LICENSE = "BSD-3-Clause"

inherit autotools

RECIPE_FLAGS += "root_tmux_conf"

COMPATIBLE_HOST_ARCHS = ".*linux"

TMUXCONF_INSTALL ?= ""
TMUX_FILES ?= ""
TMUXCONF_INSTALL:>USE_root_tmux_conf = "do_install_tmux_conf"
TMUX_FILES:>USE_root_tmux_conf = "/root/.tmux.conf"

DEPENDS += "libm libevent-dev libncurses-dev libresolv libutil"
RDEPENDS_${PN} += "libm libevent libncurses libresolv libutil"

SRC_URI  = "https://github.com/tmux/tmux/releases/download/${PV}/tmux-${PV}.tar.gz"
SRC_URI += "file://tmux.conf"

S = "${SRCDIR}/tmux-${PV}"

do_install[postfuncs] += "${TMUXCONF_INSTALL}"
do_install_tmux_conf() {
	install -d ${D}/root
	install -m 644 ${SRCDIR}/tmux.conf ${D}/root/.tmux.conf
}

FILES_${PN} += "${TMUX_FILES}"

# vim: set syntax=bitbake :

