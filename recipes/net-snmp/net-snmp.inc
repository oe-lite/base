DESCRIPTION = "Various tools relating to the Simple Network Management Protocol"
HOMEPAGE = "http://www.net-snmp.org/"
LICENSE = "BSD"

COMPATIBLE_HOST_ARCHS = ".*linux"

DEPENDS = "openssl"

inherit sysvinit siteinfo

RECIPE_FLAGS += "netsnmp_ipv6"
EXTRA_OECONF_IPV6 = "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_netsnmp_ipv6 = "--enable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"

DEFAULT_USE_netsnmp_mibs = True
RECIPE_FLAGS += "netsnmp_mibs"
EXTRA_OECONF_MIBS = "--with-out-mib-modules=examples/ucdDemoPublic --disable-mibs --disable-mib-loading"
EXTRA_OECONF_MIBS:USE_netsnmp_mibs = ""
EXTRA_OECONF += "${EXTRA_OECONF_MIBS}"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/net-snmp/net-snmp-${PV}.tar.gz"

SRC_URI += "file://init \
	    file://snmpd.conf \
	    file://snmptrapd.conf"

EXTRA_OECONF += "--enable-shared --disable-manuals --with-defaults "

do_install[postfuncs] =+ "do_install_snmp_scripts"
do_install_snmp_scripts () {
	install -d ${D}${sysconfdir}/snmp
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/snmpd
	install -m 0755 ${SRCDIR}/snmpd.conf ${D}${sysconfdir}/snmp/
	install -m 0755 ${SRCDIR}/snmptrapd.conf ${D}${sysconfdir}/snmp/
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "netsnmpagent netsnmphelpers netsnmpmibs netsnmp netsnmptrapd"

AUTO_PACKAGE_LIBS_DEPENDS += "libc libcrypto"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc libcrypto"
DEPENDS_${PN}-libnetsnmpagent += "libnetsnmp"
RDEPENDS_${PN}-libnetsnmpagent += "libnetsnmp"
DEPENDS_${PN}-libnetsnmpmibs += "libnetsnmpagent libgcc libnetsnmp"
RDEPENDS_${PN}-libnetsnmpmibs += "libnetsnmpagent libgcc libnetsnmp"
DEPENDS_${PN}-libnetsnmptrapd += "libnetsnmpagent libgcc libnetsnmp libnetsnmpmibs"
RDEPENDS_${PN}-libnetsnmptrapd += "libnetsnmpagent libgcc libnetsnmp libnetsnmpmibs"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
 agentxtrap encode_keychange fixproc ipf-mod.pl net-snmp-cert\
 net-snmp-create-v3-user snmp-bridge-mib snmpbulkget snmpbulkwalk\
 snmpcheck snmpconf snmpdelta snmpdf snmpget snmpgetnext\
 snmpinform snmptrap snmpnetstat snmpset snmpstatus snmptable\
 snmpusm snmpvacm snmpwalk tkmib snmptest snmptranslate \
 traptoemail mib2c mib2c-update net-snmp-config"

AUTO_PACKAGE_UTILS_DEPENDS += "libnetsnmp libc libcrypto"
AUTO_PACKAGE_UTILS_RDEPENDS += "libnetsnmp libc libcrypto"
DEPENDS_${PN}-snmpinform += "${PN}-snmptrap"
RDEPENDS_${PN}-snmpinform += "${PN}-snmptrap"
DEPENDS_${PN}-agentxtrap += "libnetsnmpmibs libnetsnmpagent"
RDEPENDS_${PN}-agentxtrap += "libnetsnmpmibs libnetsnmpagent"

PACKAGES =+ "${PN}-mibs ${PN}-client ${PN}-server ${PN}-conf"
DEPENDS_${PN}-server += "libc libcrypto libdl libnetsnmptrapd libnetsnmpmibs libnetsnmpagent libnetsnmp"
RDEPENDS_${PN}-server += "libnetsnmptrapd libnetsnmpmibs libnetsnmpagent libnetsnmp ${PN}-conf"
DEPENDS_${PN}-client += "${AUTO_PACKAGE_UTILS_PROVIDES}"
RDEPENDS_${PN}-client += "${AUTO_PACKAGE_UTILS_PROVIDES}"

FILES_${PN}-mibs = "${datadir}/snmp/mibs"
FILES_${PN}-client += "${datadir}/snmp"
FILES_${PN}-server += "${sysconfdir}/init.d ${sbindir}/*"
FILES_${PN}-conf += "${sysconfdir}/snmp"
