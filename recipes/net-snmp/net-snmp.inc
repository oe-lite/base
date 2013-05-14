DESCRIPTION = "Various tools relating to the Simple Network Management Protocol"
HOMEPAGE = "http://www.net-snmp.org/"
LICENSE = "BSD"

DEPENDS = "openssl"

inherit autotools-autoreconf sysvinit siteinfo

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/net-snmp/net-snmp-${PV}.tar.gz"

SRC_URI += "file://init \
	    file://snmpd.conf \
	    file://snmptrapd.conf"

EXTRA_OECONF = "--enable-shared --disable-manuals --with-defaults "

do_install[postfuncs] += "do_install_snmp_scripts"
do_install_snmp_scripts () {
	install -d ${D}${sysconfdir}/snmp
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/snmpd
	install -m 0755 ${SRCDIR}/snmpd.conf ${D}${sysconfdir}/snmp/
	install -m 0755 ${SRCDIR}/snmptrapd.conf ${D}${sysconfdir}/snmp/
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "netsnmpagent netsnmphelpers netsnmpmibs netsnmp netsnmptrapd"

AUTO_PACKAGE_LIBS_RDEPENDS += "libc"
RDEPENDS_${PN}-libnetsnmpagent += "libnetsnmp"
RDEPENDS_${PN}-libnetsnmpmibs += "libnetsnmpagent libgcc libnetsnmp"
RDEPENDS_${PN}-libnetsnmptrapd += "libnetsnmpagent libgcc libnetsnmp libnetsnmpmibs"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
 agentxtrap encode_keychange fixproc ipf-mod.pl net-snmp-cert\
 net-snmp-create-v3-user snmp-bridge-mib snmpbulkget snmpbulkwalk\
 snmpcheck snmpconf snmpdelta snmpdf snmpget snmpgetnext\
 snmpinform snmptrap snmpnetstat snmpset snmpstatus snmptable\
 snmpusm snmpvacm snmpwalk tkmib snmptest snmptranslate \
 traptoemail mib2c mib2c-update net-snmp-config"

AUTO_PACKAGE_UTILS_RDEPENDS += "libnetsnmp libc"
RDEPENDS_${PN}-snmpinform += "${PN}-snmptrap"
RDEPENDS_${PN}-agentxtrap += "libnetsnmpmibs libnetsnmpagent"

PACKAGES =+ "${PN}-mibs ${PN}-client ${PN}-server"
RDEPENDS_${PN}-server += "libnetsnmptrapd libnetsnmpmibs libnetsnmpagent libnetsnmp"
RDEPENDS_${PN}-client += "${AUTO_PACKAGE_UTILS_PROVIDES}"

FILES_${PN}-mibs = "${datadir}/snmp/mibs"
FILES_${PN}-client += "${datadir}/snmp"
FILES_${PN}-server += "${sysconfdir} ${sbindir}/*"
