DESCRIPTION = "Network Packet Capture Library"
HOMEPAGE = "http://www.tcpdump.org/"
SECTION = "libs/network"
LICENSE = "BSD"

DEPENDS = "flex-native bison-native"

DEPENDS_${PN} = "${PN}-dev"
DEPENDS_${PN}-dev = ""

RECIPE_OPTIONS += "ipv6"
EXTRA_OECONF_IPV6				= "--disable-ipv6"
EXTRA_OECONF_IPV6_RECIPE_OPTION_ipv6		= "--enable-ipv6"
EXTRA_OECONF_append += "${EXTRA_OECONF_IPV6}"

RECIPE_OPTIONS += "bluetooth"
EXTRA_OECONF_BLUETOOTH				= "--disable-bluetooth"
EXTRA_OECONF_BLUETOOTH_RECIPE_OPTION_bluetooth	= "--enable-bluetooth"
EXTRA_OECONF_append += "${EXTRA_OECONF_BLUETOOTH}"
DEPENDS_append_RECIPE_OPTION_bluetooth += "bluez-libs"

RECIPE_OPTIONS += "can"
EXTRA_OECONF_CAN				= "--disable-can"
EXTRA_OECONF_CAN_RECIPE_OPTION_can		= "--enable-can"
EXTRA_OECONF_append += "${EXTRA_OECONF_CAN}"

SRC_URI = "http://www.tcpdump.org/release/libpcap-${PV}.tar.gz"

inherit autotools siteinfo

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

# FIXME: need to add an OE-lite binconfig.bbclass
#inherit binconfig
#BINCONFIG_GLOB = "pcap-config"

FILES_${PN}	= "\
${base_libdir}/*${SOLIBS} \
${libexecdir}/* ${libdir}/lib*${SOLIBS} ${libdir}/${PN}/* \
${sysconfdir} ${sharedstatedir} ${localstatedir} \
${datadir}/${PN} \
"
FILES_${PN}-dev += "${bindir}/pcap-config"
