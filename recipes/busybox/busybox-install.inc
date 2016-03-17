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
		install -d ${D}${sysconfdir}
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

	if grep "CONFIG_UDHCPD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-udhcpd
        install -d ${D}${localstatedir}/lib/udhcpd/
        install -m 0644 /dev/null \
            ${D}${localstatedir}/lib/udhcpd/udhcpd.leases
        install -m 0644 ${S}/examples/udhcp/udhcpd.conf \
            ${D}${sysconfdir}/udhcpd.conf
	fi

	if grep "CONFIG_TFTPD=y" ${S}/.config; then
		if grep "CONFIG_INETD=y" ${S}/.config; then
			# put it where inetd class finds it, so it can be merged
			# with inetd.conf when generating image
			inetd_conf=${INETD_CONF_FILES}
			echo $USE_busybox_tftpd_inetdcmd >> $inetd_conf
		fi
		install -d ${D}${USE_busybox_tftpd_dir}
	fi

	if grep "CONFIG_FTPD=y" ${S}/.config; then
		if grep "CONFIG_INETD=y" ${S}/.config; then
			# put it where inetd class finds it, so it can be merged
			# with inetd.conf when generating image
			inetd_conf=${INETD_CONF_FILES}
		fi
		echo "ftp stream tcp nowait root ftpd ftpd -w -S ${USE_busybox_ftpd_dir}" \
			>> $inetd_conf
		install -d ${D}${USE_busybox_ftpd_dir}
	fi

	if grep "CONFIG_TELNETD=y" ${S}/.config; then
		if grep "CONFIG_INETD=y" ${S}/.config; then
			# put it where inetd class finds it, so it can be merged
			# with inetd.conf when generating image
			inetd_conf=${INETD_CONF_FILES}
		fi
		echo "telnet stream tcp nowait root telnetd telnetd" \
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
		install -d -m 0755 ${D}${localstatedir}/spool/cron/crontabs
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

	if grep "CONFIG_IFPLUGD=y" ${S}/.config; then
		sysvinit_install_script ${SRCDIR}/busybox-ifplugd
		install -d ${D}${sysconfdir}/ifplugd
		install -m 0755 ${SRCDIR}/busybox-ifplugd.action ${D}${sysconfdir}/ifplugd/ifplugd.action
		install -m 0644 ${SRCDIR}/busybox-ifplugd.conf ${D}${sysconfdir}/ifplugd/ifplugd.conf
	fi

    if grep "CONFIG_DNSD=y" ${S}/.config; then
        sysvinit_install_script ${SRCDIR}/busybox-dnsd
        install -m 0644 ${S}/examples/dnsd.conf ${D}${sysconfdir}/dnsd.conf
    fi
}

do_install[postfuncs] += "${BUSYBOX_INSTALL_POSTFUNCS}"
BUSYBOX_INSTALL_POSTFUNCS = ""
BUSYBOX_INSTALL_POSTFUNCS:>USE_busybox_mdev = " do_install_fix_mdev"

python do_install_fix_mdev () {
	import os, fileinput
	path = d.get("D")
	os.chdir(path)
	sysconfdir=d.get("sysconfdir")
	parse_state = "do_nothing"
	for line in fileinput.FileInput("." + sysconfdir + "/init.d/busybox-mdev", inplace=1):
		if d.get("USE_busybox_mdev_dash_s"):
			line=line.replace("#mdev_dash_s SECTION_START", "")
			line=line.replace("#mdev_dash_s SECTION_END", "")
		else:
			if parse_state == "do_nothing":
				if line.find("#mdev_dash_s SECTION_START") == 0:
					parse_state = "delete_line"
					line = ""
			else:
				if line.find("#mdev_dash_s SECTION_END") == 0:
					parse_state = "do_nothing"
				line = ""
		print line,
}
