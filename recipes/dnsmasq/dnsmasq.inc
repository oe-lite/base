DESCRIPTION = "dnsmasq"
HOMEPAGE = "http://www.thekelleys.org.uk/dnsmasq/doc.html"
LICENSE = "GPL-3"

SRC_URI = "http://www.thekelleys.org.uk/${PN}/${PN}-${PV}.tar.gz"
SRC_URI += "file://dnsmasq"
SRC_URI += "file://makefile.patch"

inherit c make sysvinit pkgconfig

RECIPE_FLAGS += "dnsmasq_sysvinit_start"
DEFAULT_USE_dnsmasq_sysvinit_start = "97"
DEFAULT_USE_dnsmasq_sysvinit_stop = "0"
SYSVINIT_SCRIPT_dnsmasq = "dnsmasq"

do_install[postfuncs] =+ " do_install_dnsmasq_extra"
do_install_dnsmasq_extra() {
        install -d 755 ${D}${bindir} ${D}${sysconfdir}/init.d

        install -m 755 ${SRCDIR}/dnsmasq ${D}${sysconfdir}/init.d

        install -m 755 ${S}/dnsmasq.conf.example ${D}${sysconfdir}/
        install -m 755 ${S}/dnsmasq.conf.example ${D}${sysconfdir}/dnsmasq.conf
}

PACKAGES =+ "${PN}-config"

FILES_${PN} += " ${sysconfdir} ${bindir}"
FILES_${PN}-config = "${sysconfdir}/dnsmasq.conf"

RDEPENDS_${PN} += "${PN}-config"

