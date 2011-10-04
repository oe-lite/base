# -*- mode:python; -*-
DESCRIPTION = "pkg-config is a system for managing library \
compile/link flags that works with automake and autoconf. \
It replaces the ubiquitous *-config scripts you may have \
seen with a single tool."
HOMEPAGE = "http://pkg-config.freedesktop.org/wiki/"
LICENSE = "GPL"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf pkgconfig

DEPENDS = "libdl libpthread libglib"
PKGCONFIG_DEPENDS:native = ""

SRC_URI = "http://pkgconfig.freedesktop.org/releases/pkg-config-${PV}.tar.gz"

SRC_URI += "file://common.site file://host_cpu.site"
SRC_HOST_SITEFILES = "${SRCDIR}/common.site ${SRCDIR}/host_cpu.site"

acpaths = "-I ."

EXTRA_OECONF = "--with-pc-path=''"

do_install() {
	do_install_make
	install -d -m 0755 ${D}${libdir}/pkgconfig
}
