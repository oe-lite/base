DESCRIPTION = "BusyBox: The Swiss Army Knife of Embedded Linux"
HOMEPAGE = "http://www.busybox.net"
LICENSE = "GPLv2"

inherit sysvinit runit crontab

require busybox-options.inc

SRC_URI = "http://www.busybox.net/downloads/busybox-${PV}.tar.bz2"

SRC_URI += "\
	file://defconfig \
	file://groups \
	file://inittab \
	file://rcS \
	file://rc \
	file://rcS-default \
	file://busybox-mdev \
	file://mdev.conf \
	file://busybox-klogd \
	file://busybox-syslogd \
	file://busybox-hwclock \
	file://busybox_hwclock.crontab \
	file://busybox-crond \
	file://busybox-watchdog \
	file://busybox-watchdog.runit \
	file://busybox-udhcpd \
	file://busybox-inetd \
	file://inetd.conf \
	file://busybox-ntpd \
	file://busybox-httpd \
	file://default.script \
"

SYSROOT_DEPENDS = "\
    ${TARGET_ARCH}/sysroot-libc \
    ${TARGET_ARCH}/sysroot-libm \
    ${TARGET_ARCH}/sysroot-libcrypt \
"
DEPENDS = "${SYSROOT_DEPENDS}"
RDEPENDS_${PN} = "netbase base-passwd base-files ${SYSROOT_DEPENDS}"

export EXTRA_CFLAGS = "${CFLAGS}"

require busybox-configure.inc

EXTRA_OEMAKE += "V=1 ARCH=${TARGET_ARCH} CROSS_COMPILE=${TARGET_PREFIX}"
EXTRA_OEMAKE += "CROSS=${HOST_PREFIX}"

do_compile() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	base_do_compile
}

require busybox-install.inc

FILES_${PN}_append_RECIPE_OPTION_busybox_runit += "${runitservicedir}"
FILES_${PN}_append_RECIPE_OPTION_busybox_syslogd += "${localestatedir}/log"
FILES_${PN}_append_RECIPE_OPTION_busybox_udhcpc += "${datadir}/udhcpc"
FILES_${PN}_append_RECIPE_OPTION_busybox_httpd += "/srv/www"
FILES_${PN}_append_RECIPE_OPTION_busybox_tftpd += "${RECIPE_OPTION_busybox_tftpd_dir}"
