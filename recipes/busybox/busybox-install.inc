RDEPENDS_INETD= ""
inherit inetd
INETD_CONF_FILES = "${SRCDIR}/inetd.conf.d"

#
# busybox_suid_root will be set to non-empty string if busybox needs to
# to be installed setuid root
#
busybox_suid_root = ""

do_install () {
	if grep "CONFIG_INIT=y" ${S}/.config; then
		install -d ${D}${sysconfdir}/init.d
		install -d ${D}${sysconfdir}/rcS.d
		install -d ${D}${sysconfdir}/rc0.d
		install -m 644 ${SRCDIR}/inittab ${D}${sysconfdir}/
		install -m 755 ${SRCDIR}/rcS ${D}${sysconfdir}/init.d/rcS
		install -m 755 ${SRCDIR}/rc ${D}${sysconfdir}/init.d/rc
		install -d ${D}${sysconfdir}/default
		install -m 755 ${SRCDIR}/rcS-default ${D}${sysconfdir}/default/rcS
	fi

	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	oe_runmake "CONFIG_PREFIX=${D}" install

	test -n "${busybox_suid_root}" && chmod +s ${D}${base_bindir}/busybox

	if grep "CONFIG_SYSLOGD=y" ${S}/.config; then
		install -d ${D}${localstatedir}/log
	fi

	if grep "CONFIG_RUNSVDIR=y" ${S}/.config; then
		install -d ${D}${runitservicedir}
	fi

	if grep "CONFIG_MDEV=y" ${S}/.config; then
		install -m 0644 ${SRCDIR}/mdev.conf ${D}${sysconfdir}/
	fi

	if grep "CONFIG_UDHCPC=y" ${S}/.config; then
		install -d ${D}${sysconfdir}/udhcpc.d
		install -d ${D}${datadir}/udhcpc
		install -m 0755 ${S}/examples/udhcp/simple.script \
			${D}${sysconfdir}/udhcpc.d/50default
		install -m 0755 ${SRCDIR}/default.script \
			${D}${datadir}/udhcpc/default.script
	fi

	if grep "CONFIG_INETD=y" ${S}/.config; then
		install -m 0644 ${SRCDIR}/inetd.conf ${D}${sysconfdir}/
	fi

	if grep "CONFIG_TFTPD=y" ${S}/.config; then
		if grep "CONFIG_INETD=y" ${S}/.config; then
			inetd_conf="${D}${sysconfdir}/inetd.conf"
		else
			# put it where inetd class finds it, so it can be merged
			# with inetd.conf when generating image
			inetd_conf="${SRCDIR}/inetd.conf.d"
		fi
		echo "tftp dgram udp nowait root tftpd tftpd -c ${USE_busybox_tftpd_dir}" \
			>> $inetd_conf
	fi

	if grep "CONFIG_HTTPD=y" ${S}/.config; then
		install -d ${D}/srv/www
	fi

	if grep "CONFIG_MODPROBE_SMALL=y" ${S}/.config; then
		install -d ${D}${sysconfdir}/modules
	fi

	install -m 0755 ${SRCDIR}/groups ${D}${bindir}/
	
	if grep "CONFIG_KLOGD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-klogd
	fi

	if grep "CONFIG_SYSLOGD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-syslogd
	fi

	if grep "CONFIG_MDEV=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-mdev
	fi

	if grep "CONFIG_HWCLOCK=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-hwclock
	fi

	if grep "CONFIG_CROND=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-crond
		install -d -m 0755 ${localstatedir}/spool/cron
	fi

	if grep "CONFIG_WATCHDOG=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-watchdog
	fi

	if grep "CONFIG_INETD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-inetd
	fi

	if grep "CONFIG_NTPD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-ntpd
	fi

	if grep "CONFIG_HTTPD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-httpd
	fi
}
