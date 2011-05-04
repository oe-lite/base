SECTION = "console/network"
SUMMARY = "Internet Software Consortium DHCP package"
DESCRIPTION = "DHCP (Dynamic Host Configuration Protocol) is a protocol \
which allows individual devices on an IP network to get their own \
network configuration information from a server.  DHCP helps make it \
easier to administer devices."
HOMEPAGE = "http://www.isc.org/"
LICENSE = "ISC"
LIC_FILES_CHKSUM = "file://LICENSE;beginline=4;md5=bb6fd41f5895b67088ebea61ad365e74"

inherit autotools-autoreconf

DEPENDS = "bind-dev ${TARGET_ARCH}/sysroot-libdl"

SRC_URI = "ftp://ftp.isc.org/isc/dhcp/dhcp-${PV}.tar.gz \
           file://site.h \
	       file://init-relay file://default-relay \
	       file://init-server file://default-server \
	       file://dhclient.conf file://dhcpd.conf"


TARGET_CFLAGS += "-D_GNU_SOURCE"
EXTRA_OECONF = "--with-srv-lease-file=${localstatedir}/lib/dhcp/dhcpd.leases \
                --with-srv6-lease-file=${localstatedir}/lib/dhcp/dhcpd6.leases \
                --with-cli-lease-file=${localstatedir}/lib/dhcp/dhclient.leases \
                --with-cli6-lease-file=${localstatedir}/lib/dhcp/dhclient6.leases \
                --with-libbind=${TARGET_SYSROOT}${target_libdir}/.. \
               "

CFLAGS += "-ldl"
do_compile_prepend () {
	cp -f ${SRCDIR}/site.h ${S}/includes
}

do_install_append () {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${sysconfdir}/default
	install -d ${D}${sysconfdir}/dhcp
	install -m 0755 ${SRCDIR}/init-relay ${D}${sysconfdir}/init.d/dhcp-relay
	install -m 0644 ${SRCDIR}/default-relay ${D}${sysconfdir}/default/dhcp-relay
	install -m 0755 ${SRCDIR}/init-server ${D}${sysconfdir}/init.d/dhcp-server
	install -m 0644 ${SRCDIR}/default-server ${D}${sysconfdir}/default/dhcp-server

	rm -f ${D}${sysconfdir}/dhclient.conf
	rm -f ${D}${sysconfdir}/dhcpd.conf
	install -m 0644 ${SRCDIR}/dhclient.conf ${D}${sysconfdir}/dhcp/dhclient.conf
	install -m 0644 ${SRCDIR}/dhcpd.conf ${D}${sysconfdir}/dhcp/dhcpd.conf

	install -d ${D}${base_sbindir}/
	mv ${D}${sbindir}/dhclient ${D}${base_sbindir}/
	install -m 0755 ${S}/client/scripts/linux ${D}${base_sbindir}/dhclient-script
}

PACKAGES += "${PN}-server ${PN}-client ${PN}-relay ${PN}-omshell"
FILES_${PN} = ""
FILES_${PN}-server = "${sbindir}/dhcpd ${sysconfdir}/init.d/dhcp-server ${sysconfdir}/default/dhcp-server ${sysconfdir}/dhcp/dhcpd.conf"
FILES_${PN}-relay = "${sbindir}/dhcrelay ${sysconfdir}/init.d/dhcp-relay ${sysconfdir}/default/dhcp-relay"

FILES_${PN}-client = "${base_sbindir}/dhclient ${base_sbindir}/dhclient-script ${sysconfdir}/dhcp/dhclient.conf"
RDEPENDS_${PN}-client = "sh"

FILES_${PN}-omshell = "${bindir}/omshell"

CONFFILES_${PN}-server_nylon = "/etc/dhcp/dhcpd.conf"
CONFFILES_${PN}-relay_nylon = "/etc/default/dhcp-relay"
CONFFILES_${PN}-client_nylon = "/etc/dhcp/dhclient.conf"
