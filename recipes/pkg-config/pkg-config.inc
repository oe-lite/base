DESCRIPTION = "pkg-config is a system for managing library \
compile/link flags that works with automake and autoconf. \
It replaces the ubiquitous *-config scripts you may have \
seen with a single tool."
HOMEPAGE = "http://pkg-config.freedesktop.org/wiki/"
SECTION = "console/utils"
LICENSE = "GPL"

BBCLASSEXTEND = "native sdk"

SRC_URI = "http://pkgconfig.freedesktop.org/releases/pkg-config-${PV}.tar.gz"

#DEPENDS += "glib-2.0${RE}"
#EXTRA_OECONF = "--with-installed-glib"

EXTRA_OECONF = "--with-pc-path=''"

inherit autotools

acpaths = "-I ."
do_install_append() {
	install -d -m 0755 ${D}${libdir}/pkgconfig
}
