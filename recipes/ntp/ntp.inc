DESCRIPTION = "The Network Time Protocol (NTP) is used to \
synchronize the time of a computer client or server to \
another server or reference time source, such as a radio \
or satellite receiver or modem."
HOMEPAGE = "http://www.ntp.org/"
LICENSE = "ntp"

inherit autotools-autoreconf make-vpath

DEPENDS = "${TARGET_ARCH}/sysroot-libm"

SRC_URI = "http://www.eecis.udel.edu/~ntp/ntp_spool/ntp4/ntp-4.2/${P}.tar.gz \
    file://ntp.conf \
    file://ntpd \
    file://ntpdate"

# The ac_cv_header_readline_history is to stop ntpdc depending on either
# readline or curses
EXTRA_OECONF += "\
    --without-openssl \
    --without-crypto \
    ac_cv_header_readline_history_h=no \
"
CFLAGS += " -DPTYS_ARE_GETPT -DPTYS_ARE_SEARCHED"

do_autoreconf_prepend() {
    sed -i -e 's:dist_man_MANS=	sntp.1::g' sntp/Makefile.am
}

do_install_append() {
    install -d ${D}/${sysconfdir}
    install -m 644 ${SRCDIR}/ntp.conf ${D}/${sysconfdir}
    install -d ${D}/${sysconfdir}/network/if-up.d
    install -m 755 ${SRCDIR}/ntpdate ${D}/${sysconfdir}/network/if-up.d
    install -d ${D}/${sysconfdir}/init.d
    install -m 755 ${SRCDIR}/ntpd ${D}/${sysconfdir}/init.d/ntpd
}

inherit sysvinit
RECIPE_OPTIONS += "ntpd_sysvinit_start ntpd_sysvinit_stop"
SYSVINIT_SCRIPT_ntpd = "ntpd"
DEFAULT_CONFIG_ntpd_sysvinit_start	= "25"
DEFAULT_CONFIG_ntpd_sysvinit_stop	= "25"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "ntpd ntpdate ntp-wait ntp-keygen sntp ntpq ntpdc \
    ntptime ntptrace tickadj"

# NOTE: you don't need ntpdate if you have ntpd ("ntpdc -q -g -x")

RDEPENDS_${PN}-ntpd = "${TARGET_ARCH}/sysroot-libm"
RDEPENDS_${PN}-sntp = "${TARGET_ARCH}/sysroot-libm"

EXTRA_FILES_${PN}-ntpd = "${sysconfdir}/ntp.conf \
    ${sysconfdir}/init.d/ntpd ${sysconfdir}/rc?.d/???ntpd"

EXTRA_FILES_${PN}-ntpdate = "${sysconfdir}/network/if-up.d/ntpdate"

# ntp originally includes tickadj. It's split off for inclusion in
# small firmware images on platforms with wonky clocks (e.g. OpenSlug)
RDEPENDS_${PN}-ntpd = "${PN}-tickadj"
