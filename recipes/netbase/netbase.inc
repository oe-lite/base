# -*- mode:python; -*-
DESCRIPTION = "This package provides the necessary infrastructure for basic \
	TCP/IP based networking."
LICENSE = "GPL"

RECIPE_FLAGS = "netbase_sysvinit_start netbase_sysvinit_stop netbase_auto_if"

RDEPENDS_SYSVINIT = ""
inherit sysvinit

DEFAULT_USE_netbase_sysvinit_start	= "20"
DEFAULT_USE_netbase_sysvinit_stop	= "0"
SYSVINIT_SCRIPT_netbase			= "networking"
DEFAULT_USE_netbase_auto_if		= "lo"

require conf/fetch/debian.conf
SRC_URI = "${DEBIAN_MIRROR}/main/n/netbase/netbase_${PV}.tar.gz"

SRC_URI += "file://init"
SRC_URI += "file://hosts"
SRC_URI += "file://interfaces"

do_install () {
	install -d ${D}${sysconfdir}/init.d \
		${D}${sbindir} \
		${D}${sysconfdir}/network/if-pre-up.d \
		${D}${sysconfdir}/network/if-up.d \
		${D}${sysconfdir}/network/if-down.d \
		${D}${sysconfdir}/network/if-post-down.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/networking
	install -m 0644 ${SRCDIR}/hosts ${D}${sysconfdir}/hosts
	install -m 0644 etc-rpc ${D}${sysconfdir}/rpc
	install -m 0644 etc-protocols ${D}${sysconfdir}/protocols
	install -m 0644 etc-services ${D}${sysconfdir}/services
	install -m 0644 ${SRCDIR}/interfaces \
		${D}${sysconfdir}/network/interfaces
        echo -e "\nauto ${USE_netbase_auto_if}" \
		>> ${D}${sysconfdir}/network/interfaces
}

PACKAGES = "${PN}"
