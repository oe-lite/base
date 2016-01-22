## Resolvconf - name server information handler
## Note that this recipe provide the dhclient-enter-hooks script in the dhclient-hooks package.
## This is slightly hackish as this will override the dhclient-enter-hooks on target
## However dhclient is by default not reading a hook folder but single file.
## The solution for now if multiple recipes provide the script is to not depend on  dhclient-hooks package
## and then manually merge the dhclient-enter-hooks script.

SUMMARY = "name server information handler"
DESCRIPTION = "Resolvconf is a framework for keeping track of the system's \
information about currently available nameservers. It sets \
itself up as the intermediary between programs that supply \
nameserver information and programs that need nameserver \
information."
LICENSE = "GPLv2+"
AUTHOR = "Thomas Hood"
HOMEPAGE = "http://packages.debian.org/resolvconf"

SRC_URI = "http://snapshot.debian.org/archive/debian/20150511T214718Z/pool/main/r/${PN}/${PN}_${PV}.tar.xz"
SRC_URI += "${SRC_URI_EXTRA}"

do_compile () {
	:
}

do_install () {
   install -d ${D}${libdir}/${PN}
   install -d ${D}${sysconfdir}/${PN}
   install -d ${D}${localstatedir}/run/${PN}
   install -d ${D}${localstatedir}/run/${PN}/interface
   touch ${D}${localstatedir}/run/${PN}/resolv.conf
   touch ${D}${localstatedir}/run/${PN}/enable-updates
   ln -snf ${localstatedir}/run/${PN} ${D}${sysconfdir}/${PN}/run
   ln -snf ${sysconfdir}/${PN}/run/resolv.conf ${D}${sysconfdir}/resolv.conf
   install -d ${D}${sysconfdir} ${D}${sbindir}
   install -d ${D}${mandir}/man8 ${D}${docdir}/${P}
   install -d ${D}${sysconfdir}/init.d
   install -m 0755 ${S}/debian/resolvconf.init ${D}/${sysconfdir}/init.d/resolvconf
   install -m 0755 ${S}/bin/resolvconf ${D}${sbindir}/
   install -m 0755 ${S}/bin/list-records ${D}${libdir}/${PN}
   install -m 0755 ${S}/etc/dhcp/dhclient-enter-hooks.d/resolvconf \
       ${D}${sysconfdir}/dhclient-enter-hooks
   install -d ${D}/${sysconfdir}/network/if-up.d
   install -m 0755 ${S}/debian/resolvconf.000resolvconf.if-up ${D}/${sysconfdir}/network/if-up.d/000resolvconf
   install -d ${D}/${sysconfdir}/network/if-down.d
   install -m 0755 ${S}/debian/resolvconf.resolvconf.if-down ${D}/${sysconfdir}/network/if-down.d/resolvconf
   install -m 0644 ${S}/etc/${PN}/interface-order ${D}/${sysconfdir}/${PN}/interface-order
   install -d ${D}/${sysconfdir}/${PN}/resolv.conf.d
   install -m 0644 ${S}/etc/${PN}/resolv.conf.d/base ${D}/${sysconfdir}/${PN}/resolv.conf.d/base
   install -m 0644 ${S}/etc/${PN}/resolv.conf.d/head ${D}/${sysconfdir}/${PN}/resolv.conf.d/head
   install -d ${D}/${sysconfdir}/${PN}/update.d
   install -m 0755 ${S}/etc/${PN}/update.d/libc ${D}/${sysconfdir}/${PN}/update.d/libc
   install -m 0644 README ${D}${docdir}/${P}/
   install -m 0644 ${S}/man/resolvconf.8 ${D}${mandir}/man8/
}

PACKAGES =+ "${PN}-config ${PN}-dhclient-hooks"

FILES_${PN}-config = "${sysconfdir}/${PN}/interface-order"
RDEPENDS_${PN} =+ "${PN}-config ${PN}-dhclient-hooks"

# The package does not provide a daemon as such, however it must be started before the network
# as the init script must prepare /var/run
inherit sysvinit
RECIPE_FLAGS += "resolvconf_sysvinit_start resolvconf_sysvinit_stop"
SYSVINIT_SCRIPT_resolvconf ="resolvconf"
DEFAULT_USE_resolvconf_sysvinit_start = "0"
DEFAULT_USE_resolvconf_sysvinit_stop = "0"
