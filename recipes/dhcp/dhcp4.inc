# -*- mode:python; -*-
SUMMARY = "Internet Software Consortium DHCP package"
DESCRIPTION = "DHCP (Dynamic Host Configuration Protocol) is a protocol \
	which allows individual devices on an IP network to get their own \
	network configuration information from a server.  DHCP helps make it \
	easier to administer devices."
HOMEPAGE = "http://www.isc.org/"
LICENSE = "ISC"

COMPATIBLE_HOST_ARCHS = ".*linux"

RECIPE_TYPES = "machine"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf pkgconfig

SRC_URI = "ftp://ftp.isc.org/isc/dhcp/${PV}/dhcp-${PV}.tar.gz"

SRC_URI += "${SRC_URI_EXTRA}"
SRC_URI_EXTRA += "file://init-relay"
SRC_URI_EXTRA += "file://default-relay"
SRC_URI_EXTRA += "file://init-server"
SRC_URI_EXTRA += "file://default-server"
SRC_URI_EXTRA += "file://dhclient.conf"
SRC_URI_EXTRA += "file://dhcpd.conf"

DEPENDS = "libdl"

TARGET_CFLAGS += "-D_GNU_SOURCE"
EXTRA_OECONF = "\
	--with-srv-lease-file=${localstatedir}/lib/dhcp/dhcpd.leases \
	--with-srv6-lease-file=${localstatedir}/lib/dhcp/dhcpd6.leases \
	--with-cli-lease-file=${localstatedir}/lib/dhcp/dhclient.leases \
	--with-cli6-lease-file=${localstatedir}/lib/dhcp/dhclient6.leases \
"

CFLAGS += "-ldl"

do_install[postfuncs] += "do_install_extra_files"
do_install_extra_files () {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${sysconfdir}/default
	install -d ${D}${sysconfdir}/dhcp
	install -m 0755 ${SRCDIR}/init-relay \
		${D}${sysconfdir}/init.d/dhcp-relay
	install -m 0644 ${SRCDIR}/default-relay \
		${D}${sysconfdir}/default/dhcp-relay
	install -m 0755 ${SRCDIR}/init-server \
		${D}${sysconfdir}/init.d/dhcp-server
	install -m 0644 ${SRCDIR}/default-server \
		${D}${sysconfdir}/default/dhcp-server

	mv ${D}${sysconfdir}/dhcpd.conf.example \
		${D}${sysconfdir}/dhcp/dhcpd.conf.example
	mv ${D}${sysconfdir}/dhclient.conf.example \
		${D}${sysconfdir}/dhcp/dhclient.conf.example
	install -d ${D}${base_sbindir}/
	mv ${D}${sbindir}/dhclient ${D}${base_sbindir}/
	install -m 0755 ${S}/client/scripts/linux \
		${D}${base_sbindir}/dhclient-script

	install -d ${D}${localstatedir}/lib/dhcp
}

PACKAGES += "${PN}-server ${PN}-client ${PN}-relay ${PN}-omshell ${PN}-server-config ${PN}-client-config"

COMMON_DEPENDS = "libc libdl ${CRYPTO_DEPENDS}"
CRYPTO_DEPENDS = ""
CRYPTO_DEPENDS:>USE_bind_openssl = " libcrypto libssl"

FILES_${PN} = ""
FILES_${PN}-server = "${sbindir}/dhcpd ${sysconfdir}/init.d/dhcp-server \
	${sysconfdir}/rcS.d/S*dhcp-server"
# Note that ISC does only provide a .example file, which does not work by default,
# hence it is kept as an example file
FILES_${PN}-server-config = "${sysconfdir}/default/dhcp-server \
	${sysconfdir}/dhcp/dhcpd.conf.example"
FILES_${PN}-relay = "${sbindir}/dhcrelay ${sysconfdir}/init.d/dhcp-relay \
	${sysconfdir}/default/dhcp-relay"
FILES_${PN}-client = "${base_sbindir}/dhclient ${base_sbindir}/dhclient-script"
FILES_${PN}-client-config = "${sysconfdir}/dhcp/dhclient.conf.example"
DEPENDS_${PN}-client = "${COMMON_DEPENDS}"
RDEPENDS_${PN}-client = "sh ${PN}-client-config ${COMMON_DEPENDS}"
DEPENDS_${PN}-server = "${COMMON_DEPENDS}"
RDEPENDS_${PN}-server = "${PN}-server-config ${COMMON_DEPENDS}"
DEPENDS_${PN}-relay = "${COMMON_DEPENDS}"
RDEPENDS_${PN}-relay = "${COMMON_DEPENDS}"
DEPENDS_${PN}-omshell = "${COMMON_DEPENDS}"
RDEPENDS_${PN}-omshell = "${COMMON_DEPENDS}"

FILES_${PN}-omshell = "${bindir}/omshell"

inherit sysvinit
RECIPE_FLAGS += "dhcp-server_sysvinit_start dhcp-server-sysvinit_stop"
SYSVINIT_SCRIPT_dhcp-server ="dhcp-server"
DEFAULT_USE_dhcp-server_sysvinit_start = "0"
DEFAULT_USE_dhcp-server-sysvinit_stop = "0"

RECIPE_FLAGS += "bind_openssl"
DEFAULT_USE_bind_openssl = True
EXTRA_OECONF += "${EXTRA_OECONF_OPENSSL}"
EXTRA_OECONF_OPENSSL += ""
EXTRA_OECONF_OPENSSL:USE_bind_openssl = 'LIBS="-lssl -lcrypto"'
DEPENDS:>USE_bind_openssl = " ${CRYPTO_DEPENDS}"

inherit s6rc
S6RC_LONGRUN_SERVICES = "dhcpd dhcpd-log"
SRC_URI += "file://dhcpd.run file://dhcpd-log.run"
DEFAULT_USE_dhcpd_s6rc_dependencies = "dhcpd-log net"
RECIPE_FLAGS += "dhcpd_s6rc_dependencies"
FILES_${PN}-server += "${s6rcsrcdir}"
