DESCRIPTION = "A sophisticated network protocol analyzer"
HOMEPAGE = "http://www.tcpdump.org/"
LICENSE = "BSD"

DEPENDS = "libpcap"
RDEPENDS_${PN} = "libpcap"

SRC_URI = " \
	http://www.tcpdump.org/release/tcpdump-${PV}.tar.gz \
	file://tcpdump_configure_no_-O2.patch \
	file://0001-minimal-IEEE802.15.4-allowed.patch \
	file://ipv6-cross.patch \
	file://configure.patch \
"

inherit autotools

EXTRA_OECONF = "--without-crypto"

RECIPE_OPTIONS += "ipv6"
EXTRA_OECONF_IPV6 = ""
EXTRA_OECONF_IPV6_append_RECIPE_OPTION_ipv6 = "--enable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"

#do_configure() {
#	gnu-configize
#	autoconf
#	oe_runconf
#	sed -i 's:/usr/lib:${STAGING_LIBDIR}:' ./Makefile
#	sed -i 's:/usr/include:${STAGING_INCDIR}:' ./Makefile
#}

do_install_append() {
	# tcpdump 4.0.0 installs a copy to /usr/sbin/tcpdump.4.0.0
	rm -f ${D}${sbindir}/tcpdump.${PV}
}
