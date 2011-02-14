do_configure () {
	set -e
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	oe_runmake oldconfig
}

addtask preconfigure after do_patch before do_configure
do_preconfigure[dirs] = "${S}"

do_preconfigure () {
	install -m 0644 ${SRCDIR}/defconfig ${S}/.config
}

RECIPE_OPTIONS += "busybox_init"
#
# RECIPE_OPTION_busybox_init:
#
# Default: enable sysvinit utility
DEFAULT_CONFIG_busybox_init			= "1"
# Run-time provide sysvinit feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_init += "feature/sysvinit busybox-init"
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

RECIPE_OPTIONS += "busybox_runit"
DEFAULT_CONFIG_busybox_watchdog_runit		= "0"
#
# RECIPE_OPTION_busybox_runit
#
# Default: disable runit utility
DEFAULT_CONFIG_busybox_runit			= "0"
# Run-time provides runit feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_runit += "feature/runit busybox-runit"
do_preconfigure_append_RECIPE_OPTION_busybox_runit () {
	sed -i -e 's/^# \(CONFIG_RUNSV\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_RUNSVDIR\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_RUNSVDIR_LOG\) is not set/\1=y/' \
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

RECIPE_OPTIONS += "busybox_startstopdaemon"
#
# RECIPE_OPTION_busybox_startstopdaemon
#
# Default: enable start-stop-daemon debian utility
DEFAULT_CONFIG_busybox_startstopdaemon		= "1"
# Run-time provides start-stop-daemon
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_startstopdaemon += "feature/start-stop-daemon busybox-start-stop-daemon"
do_preconfigure_append_RECIPE_OPTION_busybox_startstopdaemon () {
	sed -i -e 's/^# \(CONFIG_START_STOP_DAEMON\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_START_STOP_DAEMON_FANCY\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_START_STOP_DAEMON_LONG_OPTIONS\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_mdev \
                   busybox_mdev_sysvinit_start"
DEFAULT_CONFIG_busybox_mdev_sysvinit_start	= "10"
#
# RECIPE_OPTION_busybox_mdev
#
# Default: enable mdev utility
DEFAULT_CONFIG_busybox_mdev			= "1"
# Run-time provides mdev feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_mdev += "mdev"
do_preconfigure_append_RECIPE_OPTION_busybox_mdev () {
	sed -i -e 's/^# \(CONFIG_MDEV\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_CONF\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_RENAME\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_RENAME_REGEXP\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_EXEC\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_MDEV_LOAD_FIRMWARE\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_klogd \
                   busybox_klogd_sysvinit_start busybox_klogd_conlevel"
DEFAULT_CONFIG_busybox_klogd_sysvinit_start	= "22"
#
# RECIPE_OPTION_busybox_klogd
#
# Default: enable klogd daemon
DEFAULT_CONFIG_busybox_klogd			= "1"
# Default: only LOG_WARNING and higher go to console
DEFAULT_CONFIG_busybox_klogd_conlevel		= "5"
# Run-time provides klogd feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_klogd += "feature/klogd busybox-klogd"
do_preconfigure_append_RECIPE_OPTION_busybox_klogd () {
	sed -i -e 's/^# \(CONFIG_KLOGD\) is not set/\1=y/' \
	.config
	sed -i -e 's/^#\(CONSOLE_LEVEL\)=.*/\1="-c ${RECIPE_OPTION_busybox_klogd_conlevel}"/' ${SRCDIR}/busybox-klogd
}

RECIPE_OPTIONS += "busybox_syslogd \
					busybox_syslogd_sysvinit_start busybox_syslogd_sysvinit_stop \
					busybox_syslogd_file \
					busybox_syslogd_ipc busybox_syslogd_ipc_bufsize \
					busybox_syslogd_remote busybox_syslogd_remote_host \
					busybox_syslogd_rotate \
						busybox_syslogd_rotate_size busybox_syslogd_rotate_n"
DEFAULT_CONFIG_busybox_syslogd_sysvinit_start	= "21"
DEFAULT_CONFIG_busybox_syslogd_sysvinit_stop	= "0"
#
# RECIPE_OPTION_busybox_syslogd
#
# Default: enable syslogd daemon
DEFAULT_CONFIG_busybox_syslogd			= "1"
# Default: syslogd destination to file
DEFAULT_CONFIG_busybox_syslogd_file		= "-O /var/log/messages"
# Default: disable syslogd IPC (circular buffer) support
DEFAULT_CONFIG_busybox_syslogd_ipc		= "0"
# Default: 16 kB circular buffer
DEFAULT_CONFIG_busybox_syslogd_ipc_bufsize	= "16"
# Default: disable remote syslogd support
DEFAULT_CONFIG_busybox_syslogd_remote		= "0"
# Default: no remote host defined (should be set to -R and optionally -L args)
DEFAULT_CONFIG_busybox_syslogd_remote_host	= "0"
# Default: disable log rotate support
DEFAULT_CONFIG_busybox_syslogd_rotate		= "0"
# Default: rotate at 200 kByte
DEFAULT_CONFIG_busybox_syslogd_rotate		= "200"
# Default: keep 1 rotated logfile
DEFAULT_CONFIG_busybox_syslogd_rotate		= "1"
# Run-time provides syslogd feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_syslogd += "feature/syslogd busybox-syslogd"
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

RECIPE_OPTIONS += "busybox_logger"
#
# RECIPE_OPTION_busybox_logger
#
# Default: enable logger utility
DEFAULT_CONFIG_busybox_logger			= "1"
# Run-time provides logger feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_logger += "feature/logger busybox-logger"
do_preconfigure_append_RECIPE_OPTION_busybox_logger () {
	sed -i -e 's/^# \(CONFIG_LOGGER\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_hwclock \
					busybox_hwclock_sysvinit_start busybox_hwclock_sysvinit_stop \
					busybox_hwclock_crontab"
DEFAULT_CONFIG_busybox_hwclock_sysvinit_start	= "15"
DEFAULT_CONFIG_busybox_hwclock_sysvinit_stop	= "15"
#
# RECIPE_OPTION_busybox_hwclock
#
# Default: disable hwclock utility
DEFAULT_CONFIG_busybox_hwclock			= "1"
# Default: synchronize to rtc every hour using crond
DEFAULT_CONFIG_busybox_hwclock_crontab		= "7 * * * *"
# Run-time provides hwclock feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_hwclock += "hwclock"
do_preconfigure_append_RECIPE_OPTION_busybox_hwclock () {
	sed -i -e 's/^# \(CONFIG_HWCLOCK\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_HWCLOCK_LONG_OPTIONS\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_HWCLOCK_ADJTIME_FHS\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_cron \
					busybox_crond_sysvinit_start busybox_crond_sysvinit_stop"
DEFAULT_CONFIG_busybox_crond_sysvinit_start	= "99"
DEFAULT_CONFIG_busybox_crond_sysvinit_stop	= "0"
#
# RECIPE_OPTION_busybox_cron
#
# Default: disable cron support
DEFAULT_CONFIG_busybox_cron			= "0"
# Run-time provides crond feature and crontab
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_cron += "crond busybox-cron crontab"
do_preconfigure_append_RECIPE_OPTION_busybox_cron () {
	sed -i -e 's/^# \(CONFIG_CROND\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_CROND_D\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_CROND_CALL_SENDMAIL\) is not set/\1=y/' \
	       -e 's|^\(CONFIG_FEATURE_CROND_DIR\)=.*|\1="${localstatedir}/spool/cron"|' \
	       -e 's/^# \(CONFIG_CRONTAB\) is not set/\1=y/' \
	.config
}


RECIPE_OPTIONS += "busybox_watchdog \
					busybox_watchdog_sysvinit_start busybox_watchdog_sysvinit_stop \
					busybox_watchdog_runit \
					busybox_watchdog_dev"
DEFAULT_CONFIG_busybox_watchdog_sysvinit_start	= "70"
DEFAULT_CONFIG_busybox_watchdog_sysvinit_stop	= "01"
#
# RECIPE_OPTION_busybox_watchdog
#
# Default: disable watchdog support
DEFAULT_CONFIG_busybox_watchdog			= "0"
# Default: wathcdog device is /dev/watchdog
DEFAULT_CONFIG_busybox_watchdog_dev		= "/dev/watchdog"
# Run-time provides watchdog
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_watchdog += "watchdog"
do_preconfigure_append_RECIPE_OPTION_busybox_watchdog () {
	sed -i -e 's/^# \(CONFIG_WATCHDOG\) is not set/\1=y/' \
	.config
	sed -i -e 's|^\(WATCHDOG\)=.*|\1="${RECIPE_OPTION_busybox_watchdog_dev}"|' \
	${SRCDIR}/busybox-watchdog
	sed -i -e 's|^\(WATCHDOG\)=.*|\1="${RECIPE_OPTION_busybox_watchdog_dev}"|' \
	${SRCDIR}/busybox-watchdog.runit
}


RECIPE_OPTIONS += "busybox_udhcpc \
					busybox_udhcpc_rfc3397"
#
# RECIPE_OPTION_busybox_udhcpc
#
# Default: disable udhcp client
DEFAULT_CONFIG_busybox_udhcpc			= "1"
# Default: disable RFC3397 support
DEFAULT_CONFIG_busybox_udhcpc_rfc3397		= "1"
# Run-time provides dhcpc feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_udhcpc += "feature/dhcpc busybox-udhcpc"
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


RECIPE_OPTIONS += "busybox_udhcpd \
					busybox_udhcpd_sysvinit_start busybox_udhcpd_sysvinit_stop"
DEFAULT_CONFIG_busybox_udhcpd_sysvinit_start	= "0"
DEFAULT_CONFIG_busybox_udhcpd_sysvinit_stop	= "0"
#
# RECIPE_OPTION_busybox_udhcpd
#
# Default: disable udhcp server
DEFAULT_CONFIG_busybox_udhcpd			= "0"
# Run-time provides dhcpd features
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_udhcpd += "feature/dhcpcd busybox-udhcpd"
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

RECIPE_OPTIONS += "busybox_inetd \
					busybox_inetd_sysvinit_start"
DEFAULT_CONFIG_busybox_inetd_sysvinit_start	= "26"
#
# RECIPE_OPTION_busybox_inetd
#
# Default: disable inetd server
DEFAULT_CONFIG_busybox_inetd			= "0"
# Default: disable inetd builtin echo
DEFAULT_CONFIG_busybox_inetd_echo		= "0"
# Default: disable inetd builtin discard
DEFAULT_CONFIG_busybox_inetd_discard		= "0"
# Default: disable inetd builtin time
DEFAULT_CONFIG_busybox_inetd_time		= "0"
# Default: disable inetd builtin daytime
DEFAULT_CONFIG_busybox_inetd_daytime		= "0"
# Default: disable inetd builtin chargen
DEFAULT_CONFIG_busybox_inetd_chargen		= "0"
# Default: disable inetd builtin rpc
DEFAULT_CONFIG_busybox_inetd_rpc		= "0"
# Run-time provides inetd feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd += "feature/inetd busybox-inetd"
# Run-time provides echo-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_echo += "feature/echo-service"
# Run-time provides discard-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_discard += "feature/discard-service"
# Run-time provides time-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_time += "feature/time-service"
# Run-time provides daytime-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_daytime += "feature/daytime-service"
# Run-time provides chargen-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_chargen += "feature/chargen-service"
# Run-time provides rpc-service feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_inetd_rpc += "feature/rpc-service"
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

RECIPE_OPTIONS += "busybox_ntpd \
					busybox_ntpd_sysvinit_start \
					busybox_ntpd_server"
DEFAULT_CONFIG_busybox_ntpd_sysvinit_start	= "70"
#
# RECIPE_OPTION_busybox_ntpd
#
# Default: disable ntpd client daemon
DEFAULT_CONFIG_busybox_ntpd			= "0"
# Default: disable ntpd server support
DEFAULT_CONFIG_busybox_ntpd_server		= "0"
# Run-time provides ntpd-client feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_ntpd += "feature/ntpd-client busybox-ntpd"
# Run-time provides ntpd-server feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_ntpd_server += "feature/ntpd-server busybox-ntpd-server"
do_preconfigure_append_RECIPE_OPTION_busybox_ntpd () {
	sed -i -e 's/^# \(CONFIG_NTPD\) is not set/\1=y/' \
	.config
}
do_preconfigure_append_RECIPE_OPTION_busybox_ntpd_server () {
	sed -i -e 's/^# \(CONFIG_FEATURE_NTPD_SERVER\) is not set/\1=y/' \
	.config
}


RECIPE_OPTIONS += "busybox_httpd \
					busybox_httpd_sysvinit_start busybox_httpd_sysvinit_stop"
DEFAULT_CONFIG_busybox_httpd_sysvinit_start	= "0"
DEFAULT_CONFIG_busybox_httpd_sysvinit_stop	= "0"
#
# RECIPE_OPTION_busybox_httpd
#
# Default: disable httpd server
DEFAULT_CONFIG_busybox_httpd			= "0"
# Run-time provides httpd feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_httpd += "feature/httpd busybox-httpd"
# FIXME: add do_preconfigure stuff for busybox httpd, but it really
# should be split up into more than 1 recipe option

RECIPE_OPTIONS += "busybox_tftp"
#
# RECIPE_OPTION_busybox_tftp
#
# Default: disable tftp client
DEFAULT_CONFIG_busybox_tftp			= "0"
# Run-time provides tftp command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_tftp += "cmd/tftp busybox-tftp"
do_preconfigure_append_RECIPE_OPTION_busybox_tftp () {
	sed -i -e 's/^# \(CONFIG_TFTP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_tftpd \
					busybox_tftpd_dir"
#
# RECIPE_OPTION_busybox_tftpd
#
# Default: disable tftp daemon
DEFAULT_CONFIG_busybox_tftpd			= "0"
#
DEFAULT_CONFIG_busybox_tftpd_root		= "/tftpboot"
# Run-time provides tftpd feature
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_tftpd += "feature/tftpd busybox-tftpd"
do_preconfigure_append_RECIPE_OPTION_busybox_tftpd () {
	sed -i -e 's/^# \(CONFIG_TFTPD\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_which"
#
# RECIPE_OPTION_busybox_which
#
# Default: enable which debian utility
DEFAULT_CONFIG_busybox_which			= "0"
# Run-time provides which command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_which += "cmd/which busybox-which"
do_preconfigure_append_RECIPE_OPTION_busybox_which () {
	sed -i -e 's/^# \(CONFIG_WHICH\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_tee"
#
# RECIPE_OPTION_busybox_tee
#
# Default: enable tee debian utility
DEFAULT_CONFIG_busybox_tee			= "0"
# Run-time provides tee command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_tee += "cmd/tee busybox-tee"
do_preconfigure_append_RECIPE_OPTION_busybox_tee () {
	sed -i -e 's/^# \(CONFIG_TEE\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_FEATURE_TEE_USE_BLOCK_IO\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_su"
#
# RECIPE_OPTION_busybox_su
#
# Default: enable su command
DEFAULT_CONFIG_busybox_su			= "0"
# Run-time provides su command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_su += "cmd/su busybox-su"
# Install busybox setuid root
busybox_suid_root_append_RECIPE_OPTION_busybox_su	= "1"
do_preconfigure_append_RECIPE_OPTION_busybox_su () {
	sed -i -e 's/^# \(CONFIG_SU\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_ash"
# Default: enable ash shell
DEFAULT_CONFIG_busybox_ash			= "1"
# Run-time provides ash shell
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_ash += "busybox-ash sh getopts echo printf test"
do_preconfigure_append_RECIPE_OPTION_busybox_ash () {
	sed -i -e 's/^# \(CONFIG_ASH\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_BASH_COMPAT\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_JOB_CONTROL\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_GETOPTS\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_BUILTIN_ECHO\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_BUILTIN_PRINTF\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_BUILTIN_TEST\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_CMDCMD\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_OPTIMIZE_FOR_SIZE\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_RANDOM_SUPPORT\) is not set/\1=y/' \
	       -e 's/^# \(CONFIG_ASH_EXPAND_PRMT\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_unzip"
#
# RECIPE_OPTION_busybox_unzip
#
# Default: enable unzip utility
DEFAULT_CONFIG_busybox_unzip			= "0"
# Run-time provides unzip command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_unzip += "cmd/unzip busybox-unzip"
do_preconfigure_append_RECIPE_OPTION_busybox_unzip () {
	sed -i -e 's/^# \(CONFIG_UNZIP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_tr"
#
# RECIPE_OPTION_busybox_tr
#
# Default: enable tr utility
DEFAULT_CONFIG_busybox_tr			= "0"
# Run-time provides tr command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_tr += "cmd/tr busybox-tr"
do_preconfigure_append_RECIPE_OPTION_busybox_tr () {
	sed -i -e 's/^# \(CONFIG_TR\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_dos2unix"
#
# RECIPE_OPTION_busybox_dos2unix
#
# Default: enable dos2unix utility
DEFAULT_CONFIG_busybox_dos2unix			= "0"
# Run-time provides dos2unix command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_dos2unix += "cmd/dos2unix busybox-dos2unix"
do_preconfigure_append_RECIPE_OPTION_busybox_dos2unix () {
	sed -i -e 's/^# \(CONFIG_DOS2UNIX\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_unix2dos"
#
# RECIPE_OPTION_busybox_unix2dos
#
# Default: enable unix2dos utility
DEFAULT_CONFIG_busybox_unix2dos			= "0"
# Run-time provides unix2dos command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_unix2dos += "cmd/unix2dos busybox-unix2dos"
do_preconfigure_append_RECIPE_OPTION_busybox_unix2dos () {
	sed -i -e 's/^# \(CONFIG_UNIX2DOS\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_nice"
#
# RECIPE_OPTION_busybox_nice
#
# Default: enable nice utility
DEFAULT_CONFIG_busybox_nice			= "0"
# Run-time provides nice command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_nice += "cmd/nice busybox-nice"
do_preconfigure_append_RECIPE_OPTION_busybox_nice () {
	sed -i -e 's/^# \(CONFIG_NICE\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_sort"
#
# RECIPE_OPTION_busybox_sort
#
# Default: enable sort utility
DEFAULT_CONFIG_busybox_sort			= "0"
# Run-time provides sort command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_sort += "cmd/sort busybox-sort"
do_preconfigure_append_RECIPE_OPTION_busybox_sort () {
	sed -i -e 's/^# \(CONFIG_SORT\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_uniq"
#
# RECIPE_OPTION_busybox_uniq
#
# Default: enable uniq utility
DEFAULT_CONFIG_busybox_uniq			= "0"
# Run-time provides uniq command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_uniq += "cmd/uniq busybox-uniq"
do_preconfigure_append_RECIPE_OPTION_busybox_uniq () {
	sed -i -e 's/^# \(CONFIG_UNIQ\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_usleep"
#
# RECIPE_OPTION_busybox_usleep
#
# Default: enable usleep utility
DEFAULT_CONFIG_busybox_usleep			= "0"
# Run-time provides usleep command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_usleep += "cmd/usleep busybox-usleep"
do_preconfigure_append_RECIPE_OPTION_busybox_usleep () {
	sed -i -e 's/^# \(CONFIG_USLEEP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_who"
#
# RECIPE_OPTION_busybox_who
#
# Default: enable who utility
DEFAULT_CONFIG_busybox_who			= "0"
# Run-time provides who command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_who += "cmd/who busybox-who"
do_preconfigure_append_RECIPE_OPTION_busybox_who () {
	sed -i -e 's/^# \(CONFIG_WHO\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_whoami"
#
# RECIPE_OPTION_busybox_whoami
#
# Default: enable whoami utility
DEFAULT_CONFIG_busybox_whoami			= "0"
# Run-time provides whoami command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_whoami += "cmd/whoami busybox-whoami"
do_preconfigure_append_RECIPE_OPTION_busybox_whoami () {
	sed -i -e 's/^# \(CONFIG_WHOAMI\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_clear"
#
# RECIPE_OPTION_busybox_clear
#
# Default: enable clear utility
DEFAULT_CONFIG_busybox_clear			= "0"
# Run-time provides clear command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_clear += "cmd/clear busybox-clear"
do_preconfigure_append_RECIPE_OPTION_busybox_clear () {
	sed -i -e 's/^# \(CONFIG_CLEAR\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_resize"
#
# RECIPE_OPTION_busybox_resize
#
# Default: enable resize utility
DEFAULT_CONFIG_busybox_resize			= "0"
# Run-time provides resize command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_resize += "cmd/resize busybox-resize"
do_preconfigure_append_RECIPE_OPTION_busybox_resize () {
	sed -i -e 's/^# \(CONFIG_RESIZE\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_runlevel"
#
# RECIPE_OPTION_busybox_runlevel
#
# Default: enable runlevel utility
DEFAULT_CONFIG_busybox_runlevel			= "0"
# Run-time provides runlevel command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_runlevel += "cmd/runlevel busybox-runlevel"
do_preconfigure_append_RECIPE_OPTION_busybox_runlevel () {
	sed -i -e 's/^# \(CONFIG_RUNLEVEL\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_arp"
#
# RECIPE_OPTION_busybox_arp
#
# Default: enable arp utility
DEFAULT_CONFIG_busybox_arp			= "0"
# Run-time provides arp command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_arp += "cmd/arp busybox-arp"
do_preconfigure_append_RECIPE_OPTION_busybox_arp () {
	sed -i -e 's/^# \(CONFIG_ARP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_telnet"
#
# RECIPE_OPTION_busybox_telnet
#
# Default: enable telnet utility
DEFAULT_CONFIG_busybox_telnet			= "0"
# Run-time provides telnet command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_telnet += "cmd/telnet busybox-telnet"
do_preconfigure_append_RECIPE_OPTION_busybox_telnet () {
	sed -i -e 's/^# \(CONFIG_TELNET\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_traceroute"
#
# RECIPE_OPTION_busybox_traceroute
#
# Default: enable traceroute utility
DEFAULT_CONFIG_busybox_traceroute			= "0"
# Run-time provides traceroute command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_traceroute += "cmd/traceroute busybox-traceroute"
do_preconfigure_append_RECIPE_OPTION_busybox_traceroute () {
	sed -i -e 's/^# \(CONFIG_TRACEROUTE\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_cttyhack"
#
# RECIPE_OPTION_busybox_cttyhack
#
# Default: enable cttyhack utility
DEFAULT_CONFIG_busybox_cttyhack			= "0"
# Run-time provides cttyhack command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_cttyhack += "cmd/cttyhack busybox-cttyhack"
do_preconfigure_append_RECIPE_OPTION_busybox_cttyhack () {
	sed -i -e 's/^# \(CONFIG_CTTYHACK\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_gunzip"
#
# RECIPE_OPTION_busybox_gunzip
#
# Default: enable gunzip utility
DEFAULT_CONFIG_busybox_gunzip			= "0"
# Run-time provides gunzip command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_gunzip += "cmd/gunzip busybox-gunzip"
do_preconfigure_append_RECIPE_OPTION_busybox_gunzip () {
	sed -i -e 's/^# \(CONFIG_GUNZIP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_xargs"
#
# RECIPE_OPTION_busybox_xargs
#
# Default: enable xargs utility
DEFAULT_CONFIG_busybox_xargs			= "0"
# Run-time provides xargs command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_xargs += "cmd/xargs busybox-xargs"
do_preconfigure_append_RECIPE_OPTION_busybox_xargs () {
	sed -i -e 's/^# \(CONFIG_XARGS\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_pidof"
#
# RECIPE_OPTION_busybox_pidof
#
# Default: enable pidof utility
DEFAULT_CONFIG_busybox_pidof			= "0"
# Run-time provides pidof command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_pidof += "cmd/pidof busybox-pidof"
do_preconfigure_append_RECIPE_OPTION_busybox_pidof () {
	sed -i -e 's/^# \(CONFIG_PIDOF\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_printenv"
#
# RECIPE_OPTION_busybox_printenv
#
# Default: enable printenv utility
DEFAULT_CONFIG_busybox_printenv			= "0"
# Run-time provides printenv command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_printenv += "cmd/printenv busybox-printenv"
do_preconfigure_append_RECIPE_OPTION_busybox_printenv () {
	sed -i -e 's/^# \(CONFIG_PRINTENV\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_printf"
#
# RECIPE_OPTION_busybox_printf
#
# Default: enable printf utility
DEFAULT_CONFIG_busybox_printf			= "0"
# Run-time provides printf command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_printf += "cmd/printf busybox-printf"
do_preconfigure_append_RECIPE_OPTION_busybox_printf () {
	sed -i -e 's/^# \(CONFIG_PRINTF\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_readlink"
#
# RECIPE_OPTION_busybox_readlink
#
# Default: enable readlink utility
DEFAULT_CONFIG_busybox_readlink			= "0"
# Run-time provides readlink command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_readlink += "cmd/readlink busybox-readlink"
do_preconfigure_append_RECIPE_OPTION_busybox_readlink () {
	sed -i -e 's/^# \(CONFIG_READLINK\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_readpath"
#
# RECIPE_OPTION_busybox_readpath
#
# Default: enable readpath utility
DEFAULT_CONFIG_busybox_readpath			= "0"
# Run-time provides readpath command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_readpath += "cmd/readpath busybox-readpath"
do_preconfigure_append_RECIPE_OPTION_busybox_readpath () {
	sed -i -e 's/^# \(CONFIG_REALPATH\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_wget"
#
# RECIPE_OPTION_busybox_wget
#
# Default: enable wget utility
DEFAULT_CONFIG_busybox_wget			= "0"
# Run-time provides wget command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_wget += "cmd/wget busybox-wget"
do_preconfigure_append_RECIPE_OPTION_busybox_wget () {
	sed -i -e 's/^# \(CONFIG_WGET\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_mesg"
#
# RECIPE_OPTION_busybox_mesg
#
# Default: enable mesg utility
DEFAULT_CONFIG_busybox_mesg			= "0"
# Run-time provides mesg command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_mesg += "cmd/mesg busybox-mesg"
do_preconfigure_append_RECIPE_OPTION_busybox_mesg () {
	sed -i -e 's/^# \(CONFIG_MESG\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_tty"
#
# RECIPE_OPTION_busybox_tty
#
# Default: enable tty utility
DEFAULT_CONFIG_busybox_tty			= "0"
# Run-time provides tty command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_tty += "cmd/tty busybox-tty"
do_preconfigure_append_RECIPE_OPTION_busybox_tty () {
	sed -i -e 's/^# \(CONFIG_TTY\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_wall"
#
# RECIPE_OPTION_busybox_wall
#
# Default: enable wall utility
DEFAULT_CONFIG_busybox_wall			= "0"
# Run-time provides wall command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_wall += "cmd/wall busybox-wall"
do_preconfigure_append_RECIPE_OPTION_busybox_wall () {
	sed -i -e 's/^# \(CONFIG_WALL\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_flashcp"
#
# RECIPE_OPTION_busybox_flashcp
#
# Default: enable flashcp utility
DEFAULT_CONFIG_busybox_flashcp			= "0"
# Run-time provides flashcp command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_flashcp += "cmd/FLASHCP busybox-FLASHCP"
do_preconfigure_append_RECIPE_OPTION_busybox_flashcp () {
	sed -i -e 's/^# \(CONFIG_FLASHCP\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_flash_lock"
#
# RECIPE_OPTION_busybox_flash_lock
#
# Default: enable flash_lock utility
DEFAULT_CONFIG_busybox_flash_lock			= "0"
# Run-time provides flash_lock command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_flash_lock += "cmd/FLASHCP busybox-FLASHCP"
do_preconfigure_append_RECIPE_OPTION_busybox_flash_lock () {
	sed -i -e 's/^# \(CONFIG_FLASH_LOCK\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_flash_unlock"
#
# RECIPE_OPTION_busybox_flash_unlock
#
# Default: enable flash_unlock utility
DEFAULT_CONFIG_busybox_flash_unlock			= "0"
# Run-time provides flash_unlock command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_flash_unlock += "cmd/FLASHCP busybox-FLASHCP"
do_preconfigure_append_RECIPE_OPTION_busybox_flash_unlock () {
	sed -i -e 's/^# \(CONFIG_FLASH_UNLOCK\) is not set/\1=y/' \
	.config
}

RECIPE_OPTIONS += "busybox_flash_eraseall"
#
# RECIPE_OPTION_busybox_flash_eraseall
#
# Default: enable flash_eraseall utility
DEFAULT_CONFIG_busybox_flash_eraseall			= "0"
# Run-time provides flash_eraseall command
BUSYBOX_RPROVIDES_append_RECIPE_OPTION_busybox_flash_eraseall += "cmd/FLASHCP busybox-FLASHCP"
do_preconfigure_append_RECIPE_OPTION_busybox_flash_eraseall () {
	sed -i -e 's/^# \(CONFIG_FLASH_ERASEALL\) is not set/\1=y/' \
	.config
}
