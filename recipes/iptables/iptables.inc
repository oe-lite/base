#recipe based on iptables_1.4.21.bb from Yocto project

SUMMARY = "Tools for managing kernel packet filtering capabilities"

DESCRIPTION = "iptables is the userspace command line program used\
                to configure and control network packet filtering \
               code in Linux."

SRC_URI = "http://netfilter.org/projects/${PN}/files/${PN}-${PV}.tar.bz2"

SRC_URI += "file://types.h-add-defines-that-are-required-for-if_packet.patch \
	    file://0001-configure-Add-option-to-enable-disable-libnfnetlink.patch\
	   "

HOMEPAGE = "http://www.netfilter.org/"
BUGTRACKER = "http://bugzilla.netfilter.org/"
LICENSE = "GPL-2.0+"

FILES_${PN} =+ "${libdir}/xtables/ ${datadir}/xtables"
FILES_${PN}-dbg =+ "${libdir}/xtables/.debug"

DEPENDS = "libdl libm"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig auto-package-libs

EXTRA_OECONF = "--disable-libnfnetlink \
	      --disable-ipv6 \
"
AUTO_PACKAGE_LIBS += "ip4tc ip6tc iptc xtables"
AUTO_PACKAGE_LIBS_DEPENDS += "libc"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc"
DEPENDS_${PN}-libiptc += "libc libip4tc libip6tc"
RDEPENDS_${PN}-libiptc += "libc libip4tc libip6tc"
DEPENDS_${PN}-libxtables += "libdl"
RDEPENDS_${PN}-libxtables += "libdl"

DEPENDS_${PN} += "libc libip4tc libm libxtables"
RDEPENDS_${PN} += "libc libip4tc libm libxtables"
