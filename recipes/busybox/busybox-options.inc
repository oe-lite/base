RECIPE_OPTIONS = "\
	busybox_init \
	busybox_runit \
	busybox_startstopdaemon \
	busybox_mdev \
		busybox_mdev_sysvinit_start \
	busybox_klogd \
		busybox_klogd_sysvinit_start \
		busybox_klogd_conlevel \
	busybox_syslogd \
		busybox_syslogd_sysvinit_start busybox_syslogd_sysvinit_stop \
		busybox_syslogd_file \
		busybox_syslogd_ipc busybox_syslogd_ipc_bufsize \
		busybox_syslogd_remote busybox_syslogd_remote_host \
		busybox_syslogd_rotate \
			busybox_syslogd_rotate_size busybox_syslogd_rotate_n \
	busybox_logger \
	busybox_hwclock \
		busybox_hwclock_sysvinit_start busybox_hwclock_sysvinit_stop \
	busybox_cron \
		busybox_crond_sysvinit_start busybox_crond_sysvinit_stop \
	busybox_watchdog \
		busybox_watchdog_sysvinit_start busybox_watchdog_sysvinit_stop \
		busybox_watchdog_runit \
		busybox_watchdog_dev \
	busybox_udhcpc \
		busybox_udhcpc_rfc3397 \
	busybox_udhcpd \
		busybox_udhcpd_sysvinit_start busybox_udhcpd_sysvinit_stop \
	busybox_inetd \
		busybox_inetd_sysvinit_start \
	busybox_ntpd \
		busybox_ntpd_sysvinit_start \
		busybox_ntpd_server \
	busybox_httpd \
		busybox_httpd_sysvinit_start busybox_httpd_sysvinit_stop \
	busybox_tftp \
	busybox_tftpd \
		busybox_tftpd_dir \
	busybox_which \
	busybox_tee \
"

#
# RECIPE_OPTION_busybox_init:
#
# Default: enable sysvinit utility
DEFAULT_CONFIG_busybox_init			= "1"
# Run-time provide sysvinit feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_init += "feature/sysvinit busybox-init"

#
# RECIPE_OPTION_busybox_runit
#
# Default: disable runit utility
DEFAULT_CONFIG_busybox_runit			= "0"
# Run-time provides runit feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_runit += "feature/runit busybox-runit"

#
# RECIPE_OPTION_busybox_startstopdaemon
#
# Default: enable start-stop-daemon debian utility
DEFAULT_CONFIG_busybox_startstopdaemon		= "1"
# Run-time provides start-stop-daemon
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_startstopdaemon += "feature/start-stop-daemon busybox-start-stop-daemon"

#
# RECIPE_OPTION_busybox_mdev
#
# Default: enable mdev utility
DEFAULT_CONFIG_busybox_mdev			= "1"
# Run-time provides mdev feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_mdev += "mdev"

#
# RECIPE_OPTION_busybox_klogd
#
# Default: enable klogd daemon
DEFAULT_CONFIG_busybox_klogd			= "1"
# Default: only LOG_WARNING and higher go to console
DEFAULT_CONFIG_busybox_klogd_conlevel		= "5"
# Run-time provides klogd feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_klogd += "feature/klogd busybox-klogd"

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
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_syslogd += "feature/syslogd busybox-syslogd"

#
# RECIPE_OPTION_busybox_logger
#
# Default: enable logger utility
DEFAULT_CONFIG_busybox_logger			= "1"
# Run-time provides logger feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_logger += "feature/logger busybox-logger"

#
# RECIPE_OPTION_busybox_hwclock
#
# Default: disable hwclock utility
DEFAULT_CONFIG_busybox_hwclock			= "1"
# Run-time provides hwclock feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_hwclock += "hwclock"

#
# RECIPE_OPTION_busybox_cron
#
# Default: disable cron support
DEFAULT_CONFIG_busybox_cron			= "0"
# Run-time provides crond feature and crontab
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_cron += "feature/crond busybox-cron crontab"

#
# RECIPE_OPTION_busybox_watchdog
#
# Default: disable watchdog support
DEFAULT_CONFIG_busybox_watchdog			= "0"
# Default: wathcdog device is /dev/watchdog
DEFAULT_CONFIG_busybox_watchdog_dev		= "/dev/watchdog"
# Run-time provides watchdog
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_watchdog += "watchdog"

#
# RECIPE_OPTION_busybox_udhcpc
#
# Default: disable udhcp client
DEFAULT_CONFIG_busybox_udhcpc			= "0"
# Default: disable RFC3397 support
DEFAULT_CONFIG_busybox_udhcpc_rfc3397		= "0"
# Run-time provides dhcpc feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_udhcpc += "feature/dhcpc busybox-udhcpc"

#
# RECIPE_OPTION_busybox_udhcpd
#
# Default: disable udhcp server
DEFAULT_CONFIG_busybox_udhcpd			= "0"
# Run-time provides dhcpd features
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_udhcpd += "feature/dhcpcd busybox-udhcpd"

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
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd += "feature/inetd busybox-inetd"
# Run-time provides echo-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_echo += "feature/echo-service"
# Run-time provides discard-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_discard += "feature/discard-service"
# Run-time provides time-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_time += "feature/time-service"
# Run-time provides daytime-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_daytime += "feature/daytime-service"
# Run-time provides chargen-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_chargen += "feature/chargen-service"
# Run-time provides rpc-service feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_inetd_rpc += "feature/rpc-service"

#
# RECIPE_OPTION_busybox_ntpd
#
# Default: disable ntpd client daemon
DEFAULT_CONFIG_busybox_ntpd			= "0"
# Default: disable ntpd server support
DEFAULT_CONFIG_busybox_ntpd_server		= "0"
# Run-time provides ntpd-client feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_ntpd += "feature/ntpd-client busybox-ntpd"
# Run-time provides ntpd-server feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_ntpd_server += "feature/ntpd-server busybox-ntpd-server"

#
# RECIPE_OPTION_busybox_httpd
#
# Default: disable httpd server
DEFAULT_CONFIG_busybox_httpd			= "0"
# Run-time provides httpd feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_httpd += "feature/httpd busybox-httpd"

#
# RECIPE_OPTION_busybox_tftp
#
# Default: disable tftp client
DEFAULT_CONFIG_busybox_tftp			= "0"
# Run-time provides tftp feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_tftp += "feature/tftp busybox-tftp"

#
# RECIPE_OPTION_busybox_tftpd
#
# Default: disable tftp daemon
DEFAULT_CONFIG_busybox_tftpd			= "0"
#
DEFAULT_CONFIG_busybox_tftpd_root		= "/tftpboot"
# Run-time provides tftpd feature
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_tftpd += "feature/tftpd busybox-tftpd"

#
# RECIPE_OPTION_busybox_which
#
# Default: enable which debian utility
DEFAULT_CONFIG_busybox_which			= "0"
# Run-time provides start-stop-daemon
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_which += "util/which"

#
# RECIPE_OPTION_busybox_tee
#
# Default: enable tee debian utility
DEFAULT_CONFIG_busybox_tee			= "0"
# Run-time provides start-stop-daemon
RPROVIDES_${PN}_append_RECIPE_OPTION_busybox_tee += "util/tee"

#
# SysVinit script priorties
#
# start scripts
DEFAULT_CONFIG_busybox_klogd_sysvinit_start	= "22"
DEFAULT_CONFIG_busybox_syslogd_sysvinit_start	= "21"
DEFAULT_CONFIG_busybox_mdev_sysvinit_start	= "10"
DEFAULT_CONFIG_busybox_hwclock_sysvinit_start	= "15"
DEFAULT_CONFIG_busybox_crond_sysvinit_start	= "99"
DEFAULT_CONFIG_busybox_watchdog_sysvinit_start	= "70"
DEFAULT_CONFIG_busybox_udhcpd_sysvinit_start	= "0"
DEFAULT_CONFIG_busybox_inetd_sysvinit_start	= "26"
DEFAULT_CONFIG_busybox_ntpd_sysvinit_start	= "70"
DEFAULT_CONFIG_busybox_httpd_sysvinit_start	= "0"
# stop scripts
DEFAULT_CONFIG_busybox_syslogd_sysvinit_stop	= "0"
DEFAULT_CONFIG_busybox_hwclock_sysvinit_stop	= "15"
DEFAULT_CONFIG_busybox_crond_sysvinit_stop	= "0"
DEFAULT_CONFIG_busybox_watchdog_sysvinit_stop	= "01"
DEFAULT_CONFIG_busybox_udhcpd_sysvinit_stop	= "0"
DEFAULT_CONFIG_busybox_httpd_sysvinit_stop	= "0"

#
# Runit services
#
# enable/disable of runit services
DEFAULT_CONFIG_busybox_watchdog_runit		= "0"
