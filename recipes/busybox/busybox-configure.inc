inherit cml1

addtask preconfigure after do_patch before do_configure
do_preconfigure[dirs] = "${S}"

do_preconfigure () {
	install -m 0644 ${SRCDIR}/defconfig ${S}/.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_init () {
	sed -i -e 's/^# \(CONFIG_INIT\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_USE_INITTAB\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_KILL_REMOVED\) is not set/\1=y/' \
	       -e 's/^\(CONFIG_FEATURE_KILL_DELAY\)=.*/\1=60/' \
	       -e 's/^# \(CONFIG_FEATURE_INIT_SCTTY\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_INIT_SYSLOG\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_EXTRA_QUIET\) is not set/\1=y/' \
	       -e 's/^\(CONFIG_FEATURE_CALL_TELINIT\)=y/\1=n/' \
	       -e 's/^# \(CONFIG_SVLOGD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_CHPST\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SETUIDGID\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ENVUIDGID\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ENVDIR\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SOFTLIMIT\) is not set/\1=y/' \
	       -e 's|^# \(CONFIG_SV_DEFAULT_SERVICE_DIR\)=.*|\1="${runitservicedir}"|' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_runit () {
	sed -i -e 's/^# \(CONFIG_RUNSV\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_RUNSVDIR\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SV\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SVLOGD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_CHPST\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SETUIDGID\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ENVUIDGID\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ENVDIR\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_SOFTLIMIT\) is not set/\1=y/' \
	       -e 's|^# \(CONFIG_SV_DEFAULT_SERVICE_DIR\)=.*|\1="${runitservicedir}"|' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_startstopdaemon () {
	sed -i -e 's/^# \(CONFIG_START_STOP_DAEMON\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_START_STOP_DAEMON_FANCY\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_START_STOP_DAEMON_LONG_OPTIONS\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_mdev () {
	sed -i -e 's/^# \(CONFIG_MDEV\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_CONF\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_RENAME\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_RENAME_REGEXP\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_EXEC\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_LOAD_FIRMWARE\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_klogd () {
	sed -i -e 's/^# \(CONFIG_KLOGD\) is not set/\1=y/' \
	.config
	sed -i -e 's/^#\(CONSOLE_LEVEL\)=.*/\1="-c ${RECIPE_OPTION_busybox_klogd_conlevel}"/' ${SRCDIR}/busybox-klogd
}

do_preconfigure_append_RECIPE_OPTION_busybox_syslogd () {
	sed -i -e 's/^# \(CONFIG_SYSLOGD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_SYSLOGD_DUP\) is not set/\1=y/' \
	.config
	sed -i -e 's|^\(FILE\)=.*|\1="${RECIPE_OPTION_busybox_syslogd_file}"|' ${SRCDIR}/busybox-syslogd
}

do_preconfigure_append_RECIPE_OPTION_busybox_syslogd_ipc () {
	sed -i -e 's/^# \(CONFIG_FEATURE_IPC_SYSLOG\) is not set/\1=y/' \
	       -e 's/^\(CONFIG_FEATURE_IPC_SYSLOG_BUFFER_SIZE\)=.*/\1="${RECIPE_OPTION_busybox_syslogd_ipc_bufsize}"/' \
	       -e 's/^# \(CONFIG_LOGREAD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_syslogd_remote () {
	sed -i -e 's/^# \(CONFIG_FEATURE_REMOTE_LOG\) is not set/\1=y/' \
	.config
	sed -i -e 's/^#\(REMOTE\)=.*/\1="-R ${RECIPE_OPTION_busybox_syslogd_remote_host}"/' ${SRCDIR}/busybox-syslogd
}

do_preconfigure_append_RECIPE_OPTION_busybox_syslogd_rotate () {
	sed -i -e 's/^# \(CONFIG_FEATURE_ROTATE_LOGFILE\) is not set/\1=y/' \
	.config
	sed -i -e 's/^#\(ROTATE_SIZE\)=.*/\1="-s ${RECIPE_OPTION_busybox_syslogd_rotate_size}"/' \
	       -e 's/^#\(ROTATE_N\)=.*/\1="-b ${RECIPE_OPTION_busybox_syslogd_rotate_n}"/' \
	${SRCDIR}/busybox-syslogd
}

do_preconfigure_append_RECIPE_OPTION_busybox_logger () {
	sed -i -e 's/^# \(CONFIG_LOGGER\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_hwclock () {
	sed -i -e 's/^# \(CONFIG_HWCLOCK\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_HWCLOCK_LONG_OPTIONS\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_HWCLOCK_ADJTIME_FHS\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_cron () {
	sed -i -e 's/^# \(CONFIG_CROND\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_CROND_D\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_CROND_CALL_SENDMAIL\) is not set/\1=y/' \
	       -e 's|^\(CONFIG_FEATURE_CROND_DIR\)=.*|\1="${localstatedir}/spool/cron"|' \
	       -e 's/^# \(CONFIG_CRONTAB\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_watchdog () {
	sed -i -e 's/^# \(CONFIG_WATCHDOG\) is not set/\1=y/' \
	.config
	sed -i -e 's|^\(WATCHDOG\)=.*|\1="${RECIPE_OPTION_busybox_watchdog_dev}"|' \
	${SRCDIR}/busybox-watchdog
	sed -i -e 's|^\(WATCHDOG\)=.*|\1="${RECIPE_OPTION_busybox_watchdog_dev}"|' \
	${SRCDIR}/busybox-watchdog.runit
}

do_preconfigure_append_RECIPE_OPTION_busybox_udhcpc () {
	sed -i -e 's/^# \(CONFIG_UDHCPC\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_UDHCPC_ARPING\) is not set/\1=y/' \
	       -e 's/^\(CONFIG_UDHCPC_DEBUG\)=.*/\1=1/' \
	       -e 's|^\(CONFIG_UDHCPC_DEFAULT_SCRIPT\)=.*|\1="${datadir}/udhcpc/default.script"|' \
	       -e 's/^\(CONFIG_UDHCPC_SLACK_FOR_BUGGY_SERVERS\)=.*/\1=924/' \
	       -e 's|^\(CONFIG_IFUPDOWN_UDHCPC_CMD_OPTIONS\)=.*|\1="-R -n"|' \
	       -e 's/^\(CONFIG_FEATURE_IFUPDOWN_EXTERNAL_DHCP\)=y/\1=n/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_udhcpc_rfc3397 () {
	sed -i -e 's/^# \(CONFIG_FEATURE_UDHCP_RFC3397\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_udhcpd () {
	sed -i -e 's/^# \(CONFIG_UDHCPD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_DUMPLEASES\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_UDHCPD_WRITE_LEASES_EARLY\) is not set/\1=y/' \
	       -e 's|^\(CONFIG_DHCPD_LEASES_FILE\)=.*|\1="${localstatedir}/lib/udhcpd/udhcpd.leases"|' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_udhcpd_relay () {
	sed -i -e 's/^# \(CONFIG_DHCPRELAY\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd () {
	sed -i -e 's/^# \(CONFIG_INETD\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_echo () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_ECHO\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_discard () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_time () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_TIME\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_daytime () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_chargen () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_inetd_rpc () {
	sed -i -e 's/^# \(CONFIG_FEATURE_INETD_RPC\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_ntpd () {
	sed -i -e 's/^# \(CONFIG_NTPD\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_ntpd_server () {
	sed -i -e 's/^# \(CONFIG_FEATURE_NTPD_SERVER\) is not set/\1=y/' \
	.config
}

# FIXME: add do_preconfigure stuff for busybox httpd, but it really
# should be split up into more than 1 recipe option

do_preconfigure_append_RECIPE_OPTION_busybox_tftp () {
	sed -i -e 's/^# \(CONFIG_TFTP\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_tftpd () {
	sed -i -e 's/^# \(CONFIG_TFTPD\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_which () {
	sed -i -e 's/^# \(CONFIG_WHICH\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_tee () {
	sed -i -e 's/^# \(CONFIG_TEE\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_TEE_USE_BLOCK_IO\) is not set/\1=y/' \
	.config
}

do_preconfigure_append_RECIPE_OPTION_busybox_su () {
	sed -i -e 's/^# \(CONFIG_SU\) is not set/\1=y/' \
	.config
}
