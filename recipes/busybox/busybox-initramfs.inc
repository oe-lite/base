# busybox-watchdog sysvinit script is disabled by distro, but we need
# it in initramfs for download mode
RECIPE_USE_busybox_watchdog_sysvinit_start	= "70"

# Cannot log to appfs
RECIPE_USE_busybox_syslogd_file		= "-O /var/log/syslog"
# And no reason to rotate logfiles
RECIPE_USE_busybox_syslogd_rotate		= "0"

# Get rid of additional cruft
RECIPE_USE_busybox_cron			= "0"
RECIPE_USE_busybox_hwclock_crontab		= "0"
RECIPE_USE_busybox_ntpd			= "0"

RECIPE_USE_busybox_mdev			= "1"
RECIPE_USE_busybox_ip	= "1"
RECIPE_USE_busybox_feature_ifupdown_ip_builtin	= "1"


# Don't add all the RPROVIDES, as they should be picked up from main
# busybox recipe. When building os-initramfs, just RDEPEND on
# busybox-os-initramfs, and assume that it has the desired features.
BUSYBOX_PROVIDES = ""

FILESPATHPKG = "${P}:${PN}:busybox-${PV}:busybox:files"

S = "${SRCDIR}/busybox-${PV}"
