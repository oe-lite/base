# busybox-watchdog sysvinit script is disabled by distro, but we need
# it in initramfs for download mode
RECIPE_USE_busybox_watchdog_sysvinit_start	= "70"

# Cannot log to appfs
RECIPE_USE_busybox_syslogd_file		= "-O /var/log/syslog"
# And no reason to rotate logfiles
RECIPE_USE_busybox_syslogd_rotate		= False

# Get rid of additional cruft
RECIPE_USE_busybox_cron			= False
RECIPE_USE_busybox_hwclock_crontab		= False
RECIPE_USE_busybox_ntpd			= False

RECIPE_USE_busybox_mdev			= True
RECIPE_USE_busybox_ip	= True
RECIPE_USE_busybox_feature_ifupdown_ip_builtin	= True


# Don't add all the RPROVIDES, as they should be picked up from main
# busybox recipe. When building os-initramfs, just RDEPEND on
# busybox-os-initramfs, and assume that it has the desired features.
BUSYBOX_PROVIDES = ""
PROVIDES_${PN}-udhcpd-config = ""

FILESPATHPKG = "${P}:${PN}:busybox-${PV}:busybox:files"

S = "${SRCDIR}/busybox-${PV}"
