# -*- mode:python; -*-
DESCRIPTION = "Network Packet Capture Library"
HOMEPAGE = "http://www.tcpdump.org/"
LICENSE = "BSD"

RECIPE_TYPES = "machine"

inherit autotools siteinfo library binconfig

SRC_URI = "http://www.tcpdump.org/release/libpcap-${PV}.tar.gz"

DEPENDS = "native:flex native:bison"

RECIPE_FLAGS += "ipv6"
EXTRA_OECONF_IPV6				= "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_ipv6			= "--enable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"

RECIPE_FLAGS += "bluetooth"
EXTRA_OECONF_BLUETOOTH				= "--disable-bluetooth"
EXTRA_OECONF_BLUETOOTH:USE_bluetooth		= "--enable-bluetooth"
EXTRA_OECONF += "${EXTRA_OECONF_BLUETOOTH}"
DEPENDS:>USE_bluetooth += "bluez-libs"

RECIPE_FLAGS += "can"
EXTRA_OECONF_CAN				= "--disable-can"
EXTRA_OECONF_CAN:USE_can			= "--enable-can"
EXTRA_OECONF += "${EXTRA_OECONF_CAN}"

EXTRA_OECONF = "--with-pcap=linux"

do_compile () {
	oe_runmake
	rm -f *.o
	oe_runmake shared
}

do_install () {
	install -d ${D}${libdir}
	install -d ${D}${bindir}
	oe_runmake install DESTDIR=${D}
	oe_runmake install-shared DESTDIR=${D}

	install -d ${D}${includedir}/pcap
	install -m 0644 pcap/pcap.h ${D}${includedir}/pcap/pcap.h
	install -m 0644 pcap/namedb.h ${D}${includedir}/pcap/namedb.h
	install -m 0644 pcap/bpf.h ${D}${includedir}/pcap/bpf.h

	# Some software packages includes net/bpf.h for which the pcap-bpf.h
	# is compatible and the one to use on Linux
	install -d ${D}${includedir}/net
	ln -sf ../pcap-bpf.h ${D}${includedir}/net/bpf.h
}
