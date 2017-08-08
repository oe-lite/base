# -*- mode:python; -*-
DESCRIPTION = "This package provides the necessary infrastructure for basic \
	TCP/IP based networking."

RECIPE_FLAGS = "netbase_sysvinit_start netbase_sysvinit_stop netbase_auto_if"

RDEPENDS_SYSVINIT = ""
inherit sysvinit

DEFAULT_USE_netbase_sysvinit_start	= "20"
DEFAULT_USE_netbase_sysvinit_stop	= "0"
SYSVINIT_SCRIPT_netbase			= "networking"
DEFAULT_USE_netbase_auto_if		= "lo"

require conf/fetch/debian.conf
NETBASE_TAR_EXT ?= ".tar.gz"
SRC_URI = "${DEBIAN_MIRROR}/main/n/netbase/netbase_${PV}${NETBASE_TAR_EXT}"

SRC_URI += "file://init"
SRC_URI += "file://hosts"
SRC_URI += "file://interfaces"

do_install () {
	install -d \
		${D}${sbindir} \
		${D}${sysconfdir}/network/if-pre-up.d \
		${D}${sysconfdir}/network/if-up.d \
		${D}${sysconfdir}/network/if-down.d \
		${D}${sysconfdir}/network/if-post-down.d
	install -m 0644 ${SRCDIR}/hosts ${D}${sysconfdir}/hosts
	if [ -f ${SRCDIR}/resolv.conf ] ; then
		install -m 0644 ${SRCDIR}/resolv.conf ${D}${sysconfdir}/
	fi
	install -m 0644 etc-rpc ${D}${sysconfdir}/rpc
	install -m 0644 etc-protocols ${D}${sysconfdir}/protocols
	install -m 0644 etc-services ${D}${sysconfdir}/services
	install -m 0644 ${SRCDIR}/interfaces \
		${D}${sysconfdir}/network/interfaces
        echo -e "\nauto ${USE_netbase_auto_if}" \
		>> ${D}${sysconfdir}/network/interfaces
}

do_install[postfuncs] =+ "${do_install_SYSVINIT_SCRIPT}"
do_install_SYSVINIT_SCRIPT = ""
do_install_SYSVINIT_SCRIPT:USE_sysvinit = "do_install_sysvinit_script"
do_install_sysvinit_script() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/networking
}

PACKAGES = "${PN}-init ${PN}-hosts ${PN}-resolv-conf ${PN}-interfaces ${PN}"
RDEPENDS_${PN} = "${PN}-init ${PN}-hosts ${PN}-resolv-conf ${PN}-interfaces"
FILES_${PN}-init = "${sysconfdir}/init.d ${sysconfdir}/rc?.d"
FILES_${PN}-hosts = "${sysconfdir}/hosts"
FILES_${PN}-resolv-conf = "${sysconfdir}/resolv.conf"
FILES_${PN}-interfaces = "${sysconfdir}/network/interfaces"

inherit s6rc
SRC_URI:>USE_s6rc = " ${SRC_URI_S6RC}"
do_configure[postfuncs] += "${do_configure_netbase_s6rc}"
do_install[postfuncs] += "${do_install_netbase_s6rc}"

S6RC_BUNDLE_SERVICES += "net"
RECIPE_FLAGS += "net_s6rc_bundle"
DEFAULT_USE_net_s6rc_bundle = "net-auto net-hotplug"

S6RC_LONGRUN_SERVICES += "network-log"
SRC_URI += "file://network-log.run"
RECIPE_FLAGS += "network_log_s6rc_dependencies"

# Service for doing "ifup -a" and "ifdown -a"
S6RC_ONESHOT_SERVICES += "net-auto"
SRC_URI_S6RC += "file://net-auto.up file://net-auto.down"
RECIPE_FLAGS += "net_auto_s6rc_dependencies"
DEFAULT_USE_net_auto_s6rc_dependencies = "init-sysctl network-log"
RECIPE_FLAGS += "net_auto_s6rc_timeout_up"
DEFAULT_USE_net_auto_s6rc_timeout_up = "30000"

# Hook to generate ifplugd@ services for all allow-hotplug enabled interfaces
# and net-hotplug bundle containing all of them
SRC_URI_S6RC += "file://net-hotplug.hook file://ifplugd.run \
	file://hotplug-interfaces"
RECIPE_FLAGS += "ifplugd_s6rc_dependencies"
DEFAULT_USE_ifplugd_s6rc_dependencies = "network-log"
# re-use the busybox flag for better backwards compatibility
RECIPE_FLAGS += "busybox_ifplugd_config_args"
do_configure_netbase_s6rc:USE_s6rc += "do_configure_hotplug"
do_configure_hotplug[expand] = 3
do_configure_hotplug() {
    echo "${USE_busybox_ifplugd_config_args}" \
	 > ${SRCDIR}/ifplugd.args
    rm -f ${SRCDIR}/ifplugd.dependencies
    for dep in ${USE_ifplugd_s6rc_dependencies} ; do
	echo "$dep" \
	     >> ${SRCDIR}/ifplugd.dependencies
    done
}
do_install_netbase_s6rc:USE_s6rc += "do_install_hotplug"
do_install_hotplug() {
    mkdir -p ${D}${sysconfdir}/rc.hooks/ifplugd@.d/env
    install -m 0755 ${SRCDIR}/net-hotplug.hook \
	    ${D}${sysconfdir}/rc.hooks/net-hotplug
    install -m 0755 ${SRCDIR}/ifplugd.run \
	    ${D}${sysconfdir}/rc.hooks/ifplugd@.d/run
    install -m 0755 ${SRCDIR}/ifplugd.args \
	    ${D}${sysconfdir}/rc.hooks/ifplugd@.d/env/ARGS
    echo longrun \
	 > ${D}${sysconfdir}/rc.hooks/ifplugd@.d/type
    if test -e ${SRCDIR}/ifplugd.dependencies ; then
	install -m 0755 ${SRCDIR}/ifplugd.dependencies \
		${D}${sysconfdir}/rc.hooks/ifplugd@.d/dependencies
    fi
    install -m 0755 ${SRCDIR}/hotplug-interfaces ${D}${sbindir}
}

# Hook to generate dhcpc@ services for all dhcp enabled interfaces
SRC_URI_S6RC += "file://net-udhcpc.hook file://udhcpc.run \
	file://dhcp-interfaces"
RECIPE_FLAGS += "udhcpc_s6rc_dependencies"
DEFAULT_USE_udhcpc_s6rc_dependencies = "network-log net-rename"
# re-use the busybox flag for better backwards compatibility
RECIPE_FLAGS += "busybox_udhcpc_ifupdown_cmd_options"
do_configure_netbase_s6rc:USE_s6rc += "do_configure_udhcpc"
do_configure_udhcpc[expand] = 3
do_configure_udhcpc() {
    echo "${USE_busybox_udhcpc_ifupdown_cmd_options}" \
	 > ${SRCDIR}/udhcpc.args
    rm -f ${SRCDIR}/udhcpc.dependencies
    for dep in ${USE_udhcpc_s6rc_dependencies} ; do
	echo "$dep" \
	     >> ${SRCDIR}/udhcpc.dependencies
    done
}
do_install_netbase_s6rc:USE_s6rc += "do_install_udhcpc"
do_install_udhcpc() {
    mkdir -p ${D}${sysconfdir}/rc.hooks/udhcpc@.d/env
    install -m 0755 ${SRCDIR}/net-udhcpc.hook \
	    ${D}${sysconfdir}/rc.hooks/net-udhcpc
    install -m 0755 ${SRCDIR}/udhcpc.run \
	    ${D}${sysconfdir}/rc.hooks/udhcpc@.d/run
    install -m 0755 ${SRCDIR}/udhcpc.args \
	    ${D}${sysconfdir}/rc.hooks/udhcpc@.d/env/ARGS
    echo longrun \
	 > ${D}${sysconfdir}/rc.hooks/udhcpc@.d/type
    if test -e ${SRCDIR}/udhcpc.dependencies ; then
	install -m 0755 ${SRCDIR}/udhcpc.dependencies \
		${D}${sysconfdir}/rc.hooks/udhcpc@.d/dependencies
    fi
    install -m 0755 ${SRCDIR}/dhcp-interfaces ${D}${sbindir}
}
