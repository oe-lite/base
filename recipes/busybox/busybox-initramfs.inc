INC_PR_append = ".2"

# busybox-watchdog sysvinit script is disabled by distro, but we need
# it in initramfs for download mode
RECIPE_CONFIG_busybox_watchdog_sysvinit_start	= "70"

# Cannot log to appfs
RECIPE_CONFIG_busybox_syslogd_file		= "-O /var/log/syslog"
# And no reason to rotate logfiles
RECIPE_CONFIG_busybox_syslogd_rotate		= "0"

# Get rid of additional cruft
RECIPE_CONFIG_busybox_cron			= "0"
RECIPE_CONFIG_busybox_hwclock_crontab		= "0"
RECIPE_CONFIG_busybox_ntpd			= "0"

# Don't add all the RPROVIDES, as they should be picked up from main
# busybox recipe. When building os-initramfs, just RDEPEND on
# busybox-os-initramfs, and assume that it has the desired features.
RPROVIDES_${PN}_append = ""

FILESPATH=${@base_set_filespath([ "${FILE_DIRNAME}/${PF}", "${FILE_DIRNAME}/${P}", "${FILE_DIRNAME}/${PN}", "${FILE_DIRNAME}/${BP}", "${FILE_DIRNAME}/${BPN}", "${FILE_DIRNAME}/busybox-${PV}-${PR}", "${FILE_DIRNAME}/busybox-${PV}", "${FILE_DIRNAME}/busybox", "${FILE_DIRNAME}/files", "${FILE_DIRNAME}" ], d)}
