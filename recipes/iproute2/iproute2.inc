SUMMARY = "TCP / IP networking and traffic control utilities"
DESCRIPTION = "Iproute2 is a collection of utilities for controlling \
TCP / IP networking and traffic control in Linux.  Of the utilities ip \
and tc are the most important.  ip controls IPv4 and IPv6 \
configuration and tc stands for traffic control."
LICENSE = "GPL-2.0+"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf pkgconfig auto-package-utils

SRC_URI="https://www.kernel.org/pub/linux/utils/net/${PN}/${PN}-${PV}.tar.xz"

DEPENDS += "libdl iptables-dev libmnl"

do_configure() {
	echo "PKG_CONFIG:=pkg-config" > Config
	echo "AR:=${AR}" >> Config
	echo "CC:=${CC}" >> Config
	echo "TC_CONFIG_XT:=y" >> Config
	echo "TC_CONFIG_IPSET:=y" >> Config
	echo "IPT_LIB_DIR:=/usr/lib/xtables" >> Config
	echo "IP_CONFIG_SETNS:=y" >> Config
	echo "HAVE_MNL:=y" >> Config
	echo >> Config
	echo "%.o: %.c" >> Config
	echo "	\$(QUIET_CC)\$(CC) \$(CFLAGS) \$(EXTRA_CFLAGS) -c -o \$@ $<" >> Config
}

FILES_${PN} += "${base_libdir}/tc/*"
FILES_${PN}-dbg += "${base_libdir}/tc/.debug"

AUTO_PACKAGE_UTILS = "ifcfg ip routef routel rtmon rtpr tc"
DEPENDS_${PN}-ip += "libc libdl"
RDEPENDS_${PN}-ip += "libc libdl"
DEPENDS_${PN}-rtmon += "libc libdl"
RDEPENDS_${PN}-rtmon += "libc libdl"
DEPENDS_${PN}-tc += "libc libm libdl"
RDEPENDS_${PN}-tc += "libc libm libdl"

PACKAGES =+ " ${PN}-config"
FILES_${PN}-config = "${sysconfdir}/iproute2/*"
DEPENDS_${PN} += "libc libdl libm libmnl"
RDEPENDS_${PN} += "libc libdl libm libmnl ${PN}-config"
