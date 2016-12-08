SUMMARY = "A DHCP and DHCPv6 client"
LICENSE = "BSD-2-Clause"
HOMEPAGE = "http://roy.marples.name/projects/dhcpcd/index"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "native machine"

SRC_URI = "http://roy.marples.name/downloads/dhcpcd/dhcpcd-${PV}.tar.xz"

# This is not actually autotools-based, but it has a configure script
# with an interface similar to autotools, so we get proper do_configure,
# do_compile, do_install functions and the associated possibilites of
# hooking in via EXTRA_OECONF by (ab)using the autotools class.
inherit autotools

# pkgconfig is only used for libudev detection, but it doesn't hurt.
inherit pkgconfig

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"

RECIPE_FLAGS += "dhcpcd_udev"
DEFAULT_USE_dhcpcd_udev = False
DHCPCD_UDEV = "--without-udev"
DHCPCD_UDEV:USE_dhcpcd_udev = ""
DEPENDS:>dhcpcd_udev = " libudev libdl"
DEPENDS_${PN}:>dhcpcd_udev = " libudev libdl"
RDEPENDS_${PN}:>dhcpcd_udev = " libudev libdl"

EXTRA_OECONF += "${DHCPCD_UDEV}"

# There are configure knobs for making dhcpcd smaller (and less featureful):
#
#  --small
#  --disable-inet
#  --disable-inet6
#  --disable-auth
#  --disable-ipv4ll
#  --disable-dhcp6
#
# It's easy enough to add use flags for these, but until the need arises, we keep it simple.

# Busybox' ifup/down knows about dhcpcd, and, depending on
# configuration, may automatically call it. From
# networking/Config.src:
#
#   config FEATURE_IFUPDOWN_EXTERNAL_DHCP
#           bool "Support for external dhcp clients"
#           default n
#           depends on IFUPDOWN
#           help
#             This enables support for the external dhcp clients. Clients are
#             tried in the following order: dhcpcd, dhclient, pump and udhcpc.
#             Otherwise, if udhcpc applet is enabled, it is used.
#             Otherwise, ifup/ifdown will have no support for DHCP.
#
# So getting this right very much depends on distro configuration. All
# we can do is provide a sysvinit script which may not really be
# needed.

inherit sysvinit
SRC_URI += "file://init"
RECIPE_FLAGS += "dhcpcd_sysvinit_start dhcpcd_sysvinit_stop"
DEFAULT_USE_dhcpcd_sysvinit_start = False
DEFAULT_USE_dhcpcd_sysvinit_stop  = False
do_install_initscript() {
    sysvinit_install_script ${SRCDIR}/init dhcpcd
}
do_install[prefuncs] += "do_install_initscript"
