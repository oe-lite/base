# -*- mode:python; -*-

do_configure () {
        set -e
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake oldconfig
}

do_configure[prefuncs] += "${DO_CONFIGURE_PREFUNCS}"
DO_CONFIGURE_PREFUNCS = "do_configure_install_dot_config"
do_configure_install_dot_config () {
        install -m 0644 ${SRCDIR}/defconfig ${S}/.config
}

addhook busybox_simple_use_flags to post_recipe_parse first before set_useflags
def busybox_simple_use_flags(d):
    for flag in (d.get("BUSYBOX_SIMPLE_USE_FLAGS") or "").split():
        try:
            flag, provide = flag.split(":", 1)
            try:
                provide, config = provide.split(":", 1)
            except ValueError:
                config = ""
        except ValueError:
            provide = None
            config = ""
        try:
            flag, default = flag.split("=", 1)
        except ValueError:
            default = "0"
        if not provide:
            provide = flag
        elif provide.endswith("/"):
            provide += flag
        provide = provide.replace("_", "-")
        if not config:
            config = "CONFIG_" + flag.upper()
        configs = config.split(",")
        useflag = "busybox_" + flag.replace("-", "_")
        d.append("RECIPE_FLAGS", useflag, " ")
        if default != "0":
            d.set("DEFAULT_USE_" + useflag, default)
        d.set_override("BUSYBOX_PROVIDES", (">", "USE_" + useflag),
                       " busybox-%s %s"%(flag, provide))
        d.set_override("DO_CONFIGURE_PREFUNCS", (">", "USE_" + useflag),
                       " do_configure_" + useflag)
        function = []
        for config in configs:
            function.append("-e 's/^# \\(%s\) is not set/\\1=y/'"%(config))
        function = ("\tsed -i " +
                    " \\\n\t       ".join(function) +
                    " \\\n\t.config\n")
        funcname = "do_configure_" + useflag
        d.set(funcname, function)
        d.set_flag(funcname, "bash", True)


RECIPE_FLAGS += "busybox_init"
# USE flag: Enable sysvinit utility (boolean)
DEFAULT_USE_busybox_init = "1"
BUSYBOX_PROVIDES:>USE_busybox_init = " busybox-init sysvinit"
DO_CONFIGURE_PREFUNCS:>USE_busybox_init = " do_configure_busybox_init"
do_configure_busybox_init () {
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

RECIPE_FLAGS += "busybox_runit"
# USE flag: enable runit utility
DEFAULT_USE_busybox_runit = "0"
BUSYBOX_PROVIDES:>USE_busybox_runit = " busybox-runit runit"
DO_CONFIGURE_PREFUNCS:>USE_busybox_runit = " do_configure_busybox_runit"
do_configure_busybox_runit () {
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

BUSYBOX_SIMPLE_USE_FLAGS += "start-stop-daemon=1:util/:\
CONFIG_START_STOP_DAEMON,\
CONFIG_FEATURE_START_STOP_DAEMON_FANCY,\
CONFIG_FEATURE_START_STOP_DAEMON_LONG_OPTIONS"

BUSYBOX_SIMPLE_USE_FLAGS += "mdev=1::\
CONFIG_MDEV,\
CONFIG_FEATURE_MDEV_CONF,\
CONFIG_FEATURE_MDEV_RENAME,\
CONFIG_FEATURE_MDEV_RENAME_REGEXP,\
CONFIG_FEATURE_MDEV_EXEC,\
CONFIG_FEATURE_MDEV_LOAD_FIRMWARE"
RECIPE_FLAGS += "busybox_mdev_sysvinit_start"
DEFAULT_USE_busybox_mdev_sysvinit_start = "10"

RECIPE_FLAGS += "busybox_klogd \
        busybox_klogd_sysvinit_start busybox_klogd_conlevel"
# USE flag: enable klogd daemon
DEFAULT_USE_busybox_klogd = "1"
DEFAULT_USE_busybox_klogd_sysvinit_start = "22"
# USE flag: console log level (default: LOG_WARNING)
DEFAULT_USE_busybox_klogd_conlevel = "5"
BUSYBOX_PROVIDES:>USE_busybox_klogd = " busybox-klogd util/klogd"
DO_CONFIGURE_PREFUNCS:>USE_busybox_klogd = " do_configure_busybox_klogd"
do_configure_busybox_klogd () {
        sed -i -e 's/^# \(CONFIG_KLOGD\) is not set/\1=y/' \
        .config
        sed -i -e 's/^#\(CONSOLE_LEVEL\)=.*/\1="-c ${USE_busybox_klogd_conlevel}"/' ${SRCDIR}/busybox-klogd
}

RECIPE_FLAGS += "busybox_syslogd \
        busybox_syslogd_sysvinit_start busybox_syslogd_sysvinit_stop \
        busybox_syslogd_file \
        busybox_syslogd_ipc busybox_syslogd_ipc_bufsize \
        busybox_syslogd_remote busybox_syslogd_remote_host \
        busybox_syslogd_rotate \
        busybox_syslogd_rotate_size busybox_syslogd_rotate_n"
# USE flag: enable syslogd daemon
DEFAULT_USE_busybox_syslogd = "1"
DEFAULT_USE_busybox_syslogd_sysvinit_start = "21"
DEFAULT_USE_busybox_syslogd_sysvinit_stop  = "0"
# USE flag: syslogd destination (default: to file /var/log/messages)
DEFAULT_USE_busybox_syslogd_file = "-O /var/log/messages"
# USE flag: enable syslogd IPC (circular buffer) support
DEFAULT_USE_busybox_syslogd_ipc = "0"
# USE flag: syslogd IPC buffer size, in kByte
DEFAULT_USE_busybox_syslogd_ipc_bufsize = "16"
# USE flag: enable remote syslogd support
DEFAULT_USE_busybox_syslogd_remote = "0"
# USE flag: syslogd remote host (should be set to -R and optionally -L args)
DEFAULT_USE_busybox_syslogd_remote_host = "0"
# USE flag: enable syslogd log rotation support
DEFAULT_USE_busybox_syslogd_rotate = "0"
# USE flag: syslogd log rotation size (in kByte)
DEFAULT_USE_busybox_syslogd_rotate_size = "200"
# USE flag: number of rotated logfiles to keep
DEFAULT_USE_busybox_syslogd_rotate_n = "1"
BUSYBOX_PROVIDES:>USE_busybox_syslogd = " busybox-syslogd syslogd"
DO_CONFIGURE_PREFUNCS:>USE_busybox_syslogd = " do_configure_busybox_syslogd"
do_configure_busybox_syslogd () {
        sed -i -e 's/^# \(CONFIG_SYSLOGD\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_SYSLOGD_DUP\) is not set/\1=y/' \
        .config
        sed -i -e 's|^\(FILE\)=.*|\1="${USE_busybox_syslogd_file}"|' ${SRCDIR}/busybox-syslogd
}
DO_CONFIGURE_PREFUNCS:>USE_busybox_syslogd_ipc = " do_configure_busybox_syslogd_ipc"
do_configure_busybox_syslogd_ipc () {
        sed -i -e 's/^# \(CONFIG_FEATURE_IPC_SYSLOG\) is not set/\1=y/' \
               -e 's/^\(CONFIG_FEATURE_IPC_SYSLOG_BUFFER_SIZE\)=.*/\1="${USE_busybox_syslogd_ipc_bufsize}"/' \
               -e 's/^# \(CONFIG_LOGREAD\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING\) is not set/\1=y/' \
        .config
}
DO_CONFIGURE_PREFUNCS:>USE_busybox_syslogd_remote = " do_configure_busybox_syslogd_remote"
do_configure_busybox_syslogd_remote[precondition] = "${USE_busybox_syslogd_remote}"
do_configure_busybox_syslogd_remote () {
        sed -i -e 's/^# \(CONFIG_FEATURE_REMOTE_LOG\) is not set/\1=y/' \
        .config
        sed -i -e 's/^#\(REMOTE\)=.*/\1="-R ${USE_busybox_syslogd_remote_host}"/' ${SRCDIR}/busybox-syslogd
}
DO_CONFIGURE_PREFUNCS:>USE_busybox_syslogd_rotate = " do_configure_busybox_syslogd_rotate"
do_configure_busybox_syslogd_rotate () {
        sed -i -e 's/^# \(CONFIG_FEATURE_ROTATE_LOGFILE\) is not set/\1=y/' \
        .config
        sed -i -e 's/^#\(ROTATE_SIZE\)=.*/\1="-s ${USE_busybox_syslogd_rotate_size}"/' \
               -e 's/^#\(ROTATE_N\)=.*/\1="-b ${USE_busybox_syslogd_rotate_n}"/' \
        ${SRCDIR}/busybox-syslogd
}

BUSYBOX_SIMPLE_USE_FLAGS += "logger=1:util/"

BUSYBOX_SIMPLE_USE_FLAGS += "hwclock=1:util/:\
CONFIG_HWCLOCK,\
CONFIG_FEATURE_HWCLOCK_LONG_OPTIONS,\
CONFIG_FEATURE_HWCLOCK_ADJTIME_FHS"

RECIPE_FLAGS += "busybox_hwclock_sysvinit_start busybox_hwclock_sysvinit_stop"
DEFAULT_USE_busybox_hwclock = "1"
DEFAULT_USE_busybox_hwclock_sysvinit_start = "15"
DEFAULT_USE_busybox_hwclock_sysvinit_stop  = "15"

RECIPE_FLAGS += "busybox_hwclock_crontab"
# USE flag: synchronize to rtc every hour using crond
DEFAULT_USE_busybox_hwclock_crontab = "7 * * * *"

# USE flag: enable cron support
RECIPE_FLAGS += "busybox_cron \
        busybox_crond_sysvinit_start busybox_crond_sysvinit_stop"
DEFAULT_USE_busybox_crond_sysvinit_start = "99"
DEFAULT_USE_busybox_crond_sysvinit_stop  = "0"
BUSYBOX_PROVIDES:>USE_busybox_cron = " busybox-cron crond util/crontab"
CRONTAB_DEPENDS:USE_busybox_cron = ""
DO_CONFIGURE_PREFUNCS:>USE_busybox_cron = " do_configure_busybox_cron"
do_configure_busybox_cron () {
        sed -i -e 's/^# \(CONFIG_CROND\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_CROND_D\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_CROND_CALL_SENDMAIL\) is not set/\1=y/' \
               -e 's|^\(CONFIG_FEATURE_CROND_DIR\)=.*|\1="${localstatedir}/spool/cron"|' \
               -e 's/^# \(CONFIG_CRONTAB\) is not set/\1=y/' \
        .config
}

RECIPE_FLAGS += "busybox_watchdog \
        busybox_watchdog_sysvinit_start busybox_watchdog_sysvinit_stop \
        busybox_watchdog_runit \
        busybox_watchdog_dev"
# USE flag: enable watchdog support
DEFAULT_USE_busybox_watchdog = "0"
DEFAULT_USE_busybox_watchdog_sysvinit_start = "70"
DEFAULT_USE_busybox_watchdog_sysvinit_stop  = "01"
# USE flag: wathcdog device
DEFAULT_USE_busybox_watchdog_dev = "/dev/watchdog"
BUSYBOX_PROVIDES:>USE_busybox_watchdog = " watchdog"
DO_CONFIGURE_PREFUNCS:>USE_busybox_watchdog = " do_configure_busybox_watchdog"
do_configure_busybox_watchdog () {
        sed -i -e 's/^# \(CONFIG_WATCHDOG\) is not set/\1=y/' \
        .config
        sed -i -e 's|^\(WATCHDOG\)=.*|\1="${USE_busybox_watchdog_dev}"|' \
        ${SRCDIR}/busybox-watchdog
        sed -i -e 's|^\(WATCHDOG\)=.*|\1="${USE_busybox_watchdog_dev}"|' \
        ${SRCDIR}/busybox-watchdog.runit
}

RECIPE_FLAGS += "busybox_udhcpc \
"
# USE flag: enable udhcp client
DEFAULT_USE_busybox_udhcpc = "1"
# USE flag: enable RFC3397 support
DEFAULT_USE_busybox_udhcpc_rfc3397 = "1"
BUSYBOX_PROVIDES:>USE_busybox_udhcpc = " busybox-udhcpc dhcp-client"
DO_CONFIGURE_PREFUNCS:>USE_busybox_udhcpc = " do_configure_busybox_udhcpc"
do_configure_busybox_udhcpc () {
        sed -i -e 's/^# \(CONFIG_UDHCPC\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_UDHCPC_ARPING\) is not set/\1=y/' \
               -e 's/^\(CONFIG_UDHCPC_DEBUG\)=.*/\1=1/' \
               -e 's|^\(CONFIG_UDHCPC_DEFAULT_SCRIPT\)=.*|\1="${datadir}/udhcpc/default.script"|' \
               -e 's/^\(CONFIG_UDHCPC_SLACK_FOR_BUGGY_SERVERS\)=.*/\1=924/' \
               -e 's|^\(CONFIG_IFUPDOWN_UDHCPC_CMD_OPTIONS\)=.*|\1="-R -n"|' \
               -e 's/^\(CONFIG_FEATURE_IFUPDOWN_EXTERNAL_DHCP\)=y/\1=n/' \
        .config
}
BUSYBOX_SIMPLE_USE_FLAGS += "udhcpc_rfc3397::CONFIG_FEATURE_UDHCP_RFC3397"

RECIPE_FLAGS += "busybox_udhcpd \
        busybox_udhcpd_sysvinit_start busybox_udhcpd_sysvinit_stop"
# USE flag: enable udhcp server
DEFAULT_USE_busybox_udhcpd = "0"
DEFAULT_USE_busybox_udhcpd_sysvinit_start = "0"
DEFAULT_USE_busybox_udhcpd_sysvinit_stop  = "0"
BUSYBOX_PROVIDES:>USE_busybox_udhcpd = " busybox-udhcpd dhcp-server"
DO_CONFIGURE_PREFUNCS:>USE_busybox_udhcpd = " do_configure_busybox_udhcpd"
do_configure_busybox_udhcpd () {
        sed -i -e 's/^# \(CONFIG_UDHCPD\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_DUMPLEASES\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_UDHCPD_WRITE_LEASES_EARLY\) is not set/\1=y/' \
               -e 's|^\(CONFIG_DHCPD_LEASES_FILE\)=.*|\1="${localstatedir}/lib/udhcpd/udhcpd.leases"|' \
        .config
}
DO_CONFIGURE_PREFUNCS:>USE_busybox_udhcpd_relay = " do_configure_busybox_udhcpd_relay"
do_configure_busybox_udhcpd_relay () {
        sed -i -e 's/^# \(CONFIG_DHCPRELAY\) is not set/\1=y/' \
        .config
}

BUSYBOX_SIMPLE_USE_FLAGS += "inetd"

RECIPE_FLAGS += "busybox_inetd_sysvinit_start"
DEFAULT_USE_busybox_inetd_sysvinit_start = "26"

# USE flag: enable inetd builtin echo
BUSYBOX_SIMPLE_USE_FLAGS += "echo:service/:CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_ECHO"
# USE flag: enable inetd builtin discard
BUSYBOX_SIMPLE_USE_FLAGS += "discard:service/:CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD"
# USE flag: enable inetd builtin time
BUSYBOX_SIMPLE_USE_FLAGS += "time:service/:CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_TIME"
# USE flag: enable inetd builtin daytime
BUSYBOX_SIMPLE_USE_FLAGS += "daytime:service/:CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME"
# USE flag: enable inetd builtin chargen
BUSYBOX_SIMPLE_USE_FLAGS += "chargen:service/:CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN"
# USE flag: enable inetd builtin rpc
BUSYBOX_SIMPLE_USE_FLAGS += "rpc:service/:CONFIG_FEATURE_INETD_RPC"

# USE flag: enable ntpd client daemon
BUSYBOX_SIMPLE_USE_FLAGS += "ntpd:ntp-client"
RECIPE_FLAGS += "busybox_ntpd_sysvinit_start"
DEFAULT_USE_busybox_ntpd_sysvinit_start = "70"
# USE flag: enable ntpd server support
BUSYBOX_SIMPLE_USE_FLAGS += "ntpd_server:service/ntp:CONFIG_FEATURE_NTPD_SERVER"

# USE flag: enable httpd server
BUSYBOX_SIMPLE_USE_FLAGS += "httpd:service/http"
# FIXME: add do_configure stuff for busybox httpd, but it really
# should be split up into more than 1 recipe option
RECIPE_FLAGS += "busybox_httpd_sysvinit_start busybox_httpd_sysvinit_stop"
DEFAULT_USE_busybox_httpd_sysvinit_start = "0"
DEFAULT_USE_busybox_httpd_sysvinit_stop  = "0"

BUSYBOX_SIMPLE_USE_FLAGS += "tftp:util/:\
CONFIG_TFTP,\
CONFIG_FEATURE_TFTP_GET,\
CONFIG_FEATURE_TFTP_PUT,\
CONFIG_FEATURE_TFTP_BLOCKSIZE"

BUSYBOX_SIMPLE_USE_FLAGS += "nc:util/:\
CONFIG_NC,\
CONFIG_NC_SERVER,\
CONFIG_NC_EXTRA,\
CONFIG_NC_110_COMPAT"

# USE flag: enable tftp daemon
BUSYBOX_SIMPLE_USE_FLAGS += "tftpd:service/tftp:\
CONFIG_TFTPD,\
CONFIG_FEATURE_TFTP_GET,\
CONFIG_FEATURE_TFTP_PUT,\
CONFIG_FEATURE_TFTP_BLOCKSIZE"
RECIPE_FLAGS += "busybox_tftpd_dir"
# USE flag: tftp daemon root folder
DEFAULT_USE_busybox_tftpd_dir = "/tftpboot"

BUSYBOX_SIMPLE_USE_FLAGS += "which=1:util/"

BUSYBOX_SIMPLE_USE_FLAGS += "tee:util/:TEE,FEATURE_TEE_USE_BLOCK_IO"

BUSYBOX_SIMPLE_USE_FLAGS += "su:util/"
# Install busybox setuid root
busybox_suid_root:USE_busybox_su = "1"

RECIPE_FLAGS += "busybox_ash"
# USE flag: enable ash shell
DEFAULT_USE_busybox_ash = "1"
# Run-time provides ash shell
BUSYBOX_PROVIDES:>USE_busybox_ash += " busybox-ash sh getopts echo printf test"
DO_CONFIGURE_PREFUNCS:>USE_busybox_ash = " do_configure_busybox_ash"
do_configure_busybox_ash () {
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
               -e 's/^# \(CONFIG_SH_MATH_SUPPORT\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_SH_IS_ASH\) is not set/\1=y/' \
               -e 's/^# \(CONFIG_FEATURE_BASH_IS_ASH\) is not set/\1=y/' \
               -e 's/^\(CONFIG_FEATURE_SH_IS_NONE\)=y/# \1 is not set/' \
               -e 's/^\(CONFIG_FEATURE_BASH_IS_NONE\)=y/# \1 is not set/' \
        .config
}

# USE flag: enable ash alias
BUSYBOX_SIMPLE_USE_FLAGS += "ash_alias"

# USE flag: enable sh math support 64
BUSYBOX_SIMPLE_USE_FLAGS += "sh_math_support_64"

# USE flag: enable ash alias
BUSYBOX_SIMPLE_USE_FLAGS += "ash_alias"

# USE flag: enable feature buffers use malloc
BUSYBOX_SIMPLE_USE_FLAGS += "feature_buffers_use_malloc=1"

# USE flag: enable feature buffers go on stack
BUSYBOX_SIMPLE_USE_FLAGS += "feature_buffers_go_on_stack"

# USE flag: enable feature buffers go in bss
BUSYBOX_SIMPLE_USE_FLAGS += "feature_buffers_go_in_bss"

# USE flag: enable feature verbose usage
BUSYBOX_SIMPLE_USE_FLAGS += "feature_verbose_usage"

# USE flag: enable unzip utility
BUSYBOX_SIMPLE_USE_FLAGS += "unzip:util/"

# USE flag: enable tr utility
BUSYBOX_SIMPLE_USE_FLAGS += "tr:util/"

# USE flag: enable dos2unix utility
BUSYBOX_SIMPLE_USE_FLAGS += "dos2unix:util/"

# USE flag: enable unix2dos utility
BUSYBOX_SIMPLE_USE_FLAGS += "unix2dos:util/"

# USE flag: enable nice utility
BUSYBOX_SIMPLE_USE_FLAGS += "nice:util/"

# USE flag: enable runlevel utility
BUSYBOX_SIMPLE_USE_FLAGS += "runlevel:util/"

# USE flag: enable arp utility
BUSYBOX_SIMPLE_USE_FLAGS += "arp:util/"

# USE flag: enable traceroute utility
BUSYBOX_SIMPLE_USE_FLAGS += "traceroute:util/"

# USE flag: enable cttyhack utility
BUSYBOX_SIMPLE_USE_FLAGS += "cttyhack:util/"

# USE flag: enable gunzip utility
BUSYBOX_SIMPLE_USE_FLAGS += "gunzip:util/"

# USE flag: enable bzip2 utility
BUSYBOX_SIMPLE_USE_FLAGS += "bzip2:util/"

# USE flag: enable bunzip2 utility
BUSYBOX_SIMPLE_USE_FLAGS += "bunzip2:util/"

# USE flag: enable tar oldgnu compatibility
BUSYBOX_SIMPLE_USE_FLAGS += "feature_tar_oldgnu_compatibility"

# USE flag: enable unxz utility
BUSYBOX_SIMPLE_USE_FLAGS += "unxz:util/"

# USE flag: enable unlzma utility
BUSYBOX_SIMPLE_USE_FLAGS += "unlzma:util/"

# USE flag: enable lzop utility
BUSYBOX_SIMPLE_USE_FLAGS += "lzop:util/"

# USE flag: enable feature date isofmt
BUSYBOX_SIMPLE_USE_FLAGS += "feature_date_isofmt"

# USE flag: enable feature date nano
BUSYBOX_SIMPLE_USE_FLAGS += "feature_date_nano"

# USE flag: enable feature date compat
BUSYBOX_SIMPLE_USE_FLAGS += "feature_date_compat"

# USE flag: enable tr utility
BUSYBOX_SIMPLE_USE_FLAGS += "tr:util/"

# USE flag: enable install utility
BUSYBOX_SIMPLE_USE_FLAGS += "install:util/"

# USE flag: enable feature ls filetypes
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_filetypes=1"

# USE flag: enable feature ls followlinks
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_followlinks=1"

# USE flag: enable feature ls recursive
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_recursive=1"

# USE flag: enable feature ls sortfiles
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_sortfiles=1"

# USE flag: enable feature ls timestamps
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_timestamps=1"

# USE flag: enable feature ls username
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_username=1"

# USE flag: enable feature ls color
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_color"

# USE flag: enable feature ls color is default
BUSYBOX_SIMPLE_USE_FLAGS += "feature_ls_color_is_default"

# USE flag: enable sort utility
BUSYBOX_SIMPLE_USE_FLAGS += "sort:util/"

# USE flag: enable feature fancy tail
BUSYBOX_SIMPLE_USE_FLAGS += "feature_fancy_tail"

# USE flag: enable tee utility
BUSYBOX_SIMPLE_USE_FLAGS += "tee:util/"

# USE flag: enable feature tee use block io
BUSYBOX_SIMPLE_USE_FLAGS += "feature_tee_use_block_io"

# USE flag: enable tty utility
BUSYBOX_SIMPLE_USE_FLAGS += "tty:util/"

# USE flag: enable uniq utility
BUSYBOX_SIMPLE_USE_FLAGS += "uniq:util/"

# USE flag: enable usleep utility
BUSYBOX_SIMPLE_USE_FLAGS += "usleep:util/"

# USE flag: enable wc utility
BUSYBOX_SIMPLE_USE_FLAGS += "wc:util/"

# USE flag: enable who utility
BUSYBOX_SIMPLE_USE_FLAGS += "who:util/"

# USE flag: enable whoami utility
BUSYBOX_SIMPLE_USE_FLAGS += "whoami:util/"

# USE flag: enable feature preserve hardlinks
BUSYBOX_SIMPLE_USE_FLAGS += "feature_preserve_hardlinks"

# USE flag: enable chvt utility
BUSYBOX_SIMPLE_USE_FLAGS += "chvt:util/"

# USE flag: enable clear utility
BUSYBOX_SIMPLE_USE_FLAGS += "clear:util/"

# USE flag: enable deallocvt utility
BUSYBOX_SIMPLE_USE_FLAGS += "deallocvt:util/"

# USE flag: enable openvt utility
BUSYBOX_SIMPLE_USE_FLAGS += "openvt:util/"

# USE flag: enable resize utility
BUSYBOX_SIMPLE_USE_FLAGS += "resize:util/"

# USE flag: enable feature vi readonly
BUSYBOX_SIMPLE_USE_FLAGS += "feature_vi_readonly"

# USE flag: enable feature vi setopts
BUSYBOX_SIMPLE_USE_FLAGS += "feature_vi_setopts"

# USE flag: enable feature vi set
BUSYBOX_SIMPLE_USE_FLAGS += "feature_vi_set"

# USE flag: enable grep utility
BUSYBOX_SIMPLE_USE_FLAGS += "grep=1:util/"

# USE flag: enable feature grep egrep alias
BUSYBOX_SIMPLE_USE_FLAGS += "feature_grep_egrep_alias=1"

# USE flag: enable feature grep fgrep alias
BUSYBOX_SIMPLE_USE_FLAGS += "feature_grep_fgrep_alias"

# USE flag: enable feature grep context
BUSYBOX_SIMPLE_USE_FLAGS += "feature_grep_context"

# USE flag: enable xargs utility
BUSYBOX_SIMPLE_USE_FLAGS += "xargs:util/"

# USE flag: enable feature xargs support confirmation
BUSYBOX_SIMPLE_USE_FLAGS += "feature_xargs_support_confirmation"

# USE flag: enable feature xargs support quotes
BUSYBOX_SIMPLE_USE_FLAGS += "feature_xargs_support_quotes"

# USE flag: enable feature xargs support termopt
BUSYBOX_SIMPLE_USE_FLAGS += "feature_xargs_support_termopt"

# USE flag: enable feature xargs support zero term
BUSYBOX_SIMPLE_USE_FLAGS += "feature_xargs_support_zero_term"

# USE flag: enable feature shadowpasswds
BUSYBOX_SIMPLE_USE_FLAGS += "feature_shadowpasswds"

# USE flag: enable feature securetty
BUSYBOX_SIMPLE_USE_FLAGS += "feature_securetty"

# USE flag: enable feature_mount nfs
BUSYBOX_SIMPLE_USE_FLAGS += "feature_mount_nfs"

# USE flag: enable pivot root utility
BUSYBOX_SIMPLE_USE_FLAGS += "pivot_root:util/"

# USE flag: enable rdate utility
BUSYBOX_SIMPLE_USE_FLAGS += "rdate:util/"

# USE flag: enable swaponoff utility
BUSYBOX_SIMPLE_USE_FLAGS += "swaponoff:util/"

# USE flag: enable feature mount loop
BUSYBOX_SIMPLE_USE_FLAGS += "feature_mount_loop"

# USE flag: enable pidof utility
BUSYBOX_SIMPLE_USE_FLAGS += "pidof:util/"

# USE flag: enable printenv utility
BUSYBOX_SIMPLE_USE_FLAGS += "printenv:util/"

# USE flag: enable printf utility
BUSYBOX_SIMPLE_USE_FLAGS += "printf:util/"

# USE flag: enable readlink utility
BUSYBOX_SIMPLE_USE_FLAGS += "readlink:util/"

# USE flag: enable readpath utility
BUSYBOX_SIMPLE_USE_FLAGS += "readpath:util/"

# USE flag: enable telnet utility
BUSYBOX_SIMPLE_USE_FLAGS += "telnet:util/"

# USE flag: enable feature telnet ttype
BUSYBOX_SIMPLE_USE_FLAGS += "feature_telnet_ttype"

# USE flag: enable feature telnet autologin
BUSYBOX_SIMPLE_USE_FLAGS += "feature_telnet_autologin"

# USE flag: enable telnetd utility
BUSYBOX_SIMPLE_USE_FLAGS += "telnetd:util/"

# USE flag: enable wget utility
BUSYBOX_SIMPLE_USE_FLAGS += "wget:util/"

# USE flag: enable feature wget statusbar
BUSYBOX_SIMPLE_USE_FLAGS += "feature_wget_statusbar"

# USE flag: enable feature wget authentication
BUSYBOX_SIMPLE_USE_FLAGS += "feature_wget_authentication"

# USE flag: enable renice utility
BUSYBOX_SIMPLE_USE_FLAGS += "renice:util/"

# USE flag: enable mesg utility
BUSYBOX_SIMPLE_USE_FLAGS += "mesg:util/"

# USE flag: enable tty utility
BUSYBOX_SIMPLE_USE_FLAGS += "tty:util/"

# USE flag: enable wall utility
BUSYBOX_SIMPLE_USE_FLAGS += "wall:util/"

# USE flag: enable cmp utility
BUSYBOX_SIMPLE_USE_FLAGS += "cmp:util/"

# USE flag: enable flashcp utility
BUSYBOX_SIMPLE_USE_FLAGS += "flashcp:util/"

# USE flag: enable flash_lock utility
BUSYBOX_SIMPLE_USE_FLAGS += "flash_lock:util/"

# USE flag: enable flash_unlock utility
BUSYBOX_SIMPLE_USE_FLAGS += "flash_unlock:util/"

# USE flag: enable flash_eraseall utility
BUSYBOX_SIMPLE_USE_FLAGS += "flash_eraseall:util/"

# USE flag: enable ftpget utility
BUSYBOX_SIMPLE_USE_FLAGS += "ftpget:util/"

# USE flag: enable ftpput utility
BUSYBOX_SIMPLE_USE_FLAGS += "ftpput:util/"

# USE flag: enable >2GB file support
BUSYBOX_SIMPLE_USE_FLAGS += "lfs"

# USE flag: enable less utility
BUSYBOX_SIMPLE_USE_FLAGS += "less=1:util/"

# USE flag: enable less_regexp utility
BUSYBOX_SIMPLE_USE_FLAGS += "less_regexp:util/"

RECIPE_FLAGS += "busybox_inittab_login"
#
# USE_busybox_inittab_login
#
# USE flag: enable inittab_login utility
DEFAULT_USE_busybox_inittab_login = "::askfirst:-/bin/sh"
# Run-time provides inittab_login command
BUSYBOX_PROVIDES:>USE_busybox_inittab_login += " busybox-inittab-login util/inittab-login"
DO_CONFIGURE_PREFUNCS:>USE_busybox_inittab_login = " do_configure_busybox_inittab_login"
do_configure_busybox_inittab_login () {
        sed -i -e 's#::askfirst:-/bin/sh#${USE_busybox_inittab_login}#' ${SRCDIR}/inittab
}

RECIPE_FLAGS += "busybox_inittab_extras"
#
# USE_busybox_inittab_extras
#
# USE flag: No extras
DEFAULT_USE_busybox_inittab_extras = ""
# Space seperated strings busybox_inittab_extras added to inittab
DO_CONFIGURE_PREFUNCS:>USE_busybox_inittab_extras = " do_configure_busybox_inittab_extras"
def do_configure_busybox_inittab_extras(d):
    srcdir = d.get("SRCDIR")
    with open(os.path.join(srcdir, "inittab"), "a") as inittab:
        for extra in d.get("USE_busybox_inittab_extras").split():
            inittab.write(extra + "\n")
