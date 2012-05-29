DESCRIPTION = "DHCP (Dynamic Host Configuration Protocol) is a protocol \
which allows individual devices on an IP network to get their own \
network configuration information from a server.  DHCP helps make it \
easier to administer devices."
HOMEPAGE = "http://www.isc.org/"

RECIPE_TYPES = "machine"

inherit c make

SRC_URI = "ftp://ftp.isc.org/isc/dhcp/dhcp-${PV}.tar.gz \
    file://init-relay file://default-relay \
    file://init-server file://default-server \
    file://linux30.patch \
    file://dhclient.conf file://dhcpd.conf"

S = "${SRCDIR}/dhcp-${PV}"

do_configure() {
    ./configure
}

EXTRA_OEMAKE += "VARDB=${localstatedir}/lib/dhcp VARRUN=${localstatedir}/run"

EXTRA_OEMAKE_COMPILE += "RANLIB=${RANLIB} \
    PREDEFINES='\
        -D_PATH_DHCPD_PID=\\\"${localstatedir}/run/dhcpd.pid\\\" \
        -D_PATH_DHCPD_DB=\\\"${localstatedir}/lib/dhcp/dhcpd.leases\\\" \
        -D_PATH_DHCPD_CONF=\\\"${sysconfdir}/dhcp/dhcpd.conf\\\" \
        -D_PATH_DHCLIENT_PID=\\\"${localstatedir}/run/dhclient.pid\\\" \
        -D_PATH_DHCLIENT_DB=\\\"${localstatedir}/lib/dhcp/dhclient.leases\\\" \
        -D_PATH_DHCLIENT_SCRIPT=\\\"${base_sbindir}/dhclient-script\\\" \
        -D_PATH_DHCLIENT_CONF=\\\"${sysconfdir}/dhcp/dhclient.conf\\\" \
    '\
"

EXTRA_OEMAKE_INSTALL += "INCDIR=${includedir} LIBDIR=${libdir} \
    USRMANDIR=${mandir}/man1 ADMMANDIR=${mandir}/man8 \
    FFMANDIR=${mandir}/man5 LIBMANDIR=${mandir}/man3"

do_install() {
    do_install_make
    install -d ${D}${sysconfdir}/init.d
    install -d ${D}${sysconfdir}/default
    install -d ${D}${sysconfdir}/dhcp
    install -m 0755 ${SRCDIR}/init-relay ${D}${sysconfdir}/init.d/dhcp-relay
    install -m 0644 ${SRCDIR}/default-relay ${D}${sysconfdir}/default/dhcp-relay
    install -m 0755 ${SRCDIR}/init-server ${D}${sysconfdir}/init.d/dhcp-server
    install -m 0644 ${SRCDIR}/default-server ${D}${sysconfdir}/default/dhcp-server
    install -m 0644 ${SRCDIR}/dhclient.conf ${D}${sysconfdir}/dhcp/dhclient.conf
    install -m 0644 ${SRCDIR}/dhcpd.conf ${D}${sysconfdir}/dhcp/dhcpd.conf
    install -d ${D}${localstatedir}/lib/dhcp
}

PACKAGES += "${PN}-server ${PN}-client ${PN}-relay ${PN}-omshell"
FILES_${PN} = ""
FILES_${PN}-server = "${sbindir}/dhcpd ${sysconfdir}/init.d/dhcp-server ${sysconfdir}/default/dhcp-server ${sysconfdir}/dhcp/dhcpd.conf"
FILES_${PN}-relay = "${sbindir}/dhcrelay ${sysconfdir}/init.d/dhcp-relay ${sysconfdir}/default/dhcp-relay"

FILES_${PN}-client = "${base_sbindir}/dhclient ${base_sbindir}/dhclient-script ${sysconfdir}/dhcp/dhclient.conf \
    ${localstatedir}/lib/dhcp"

RDEPENDS_${PN}-client = "sh"

FILES_${PN}-omshell = "${bindir}/omshell"
