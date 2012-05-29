# -*- mode:python; -*-
DESCRIPTION = "The Network Time Protocol (NTP) is used to synchronize the time \
	of a computer client or server to another server or reference time \
	source, such as a radio or satellite receiver or modem."
HOMEPAGE = "http://www.ntp.org/"

RECIPE_TYPES = "machine"

inherit autotools-autoreconf make-vpath

DEPENDS = "libm"

SRC_URI = "http://www.eecis.udel.edu/~ntp/ntp_spool/ntp4/ntp-4.2/${P}.tar.gz"
SRC_URI += "file://ntp.conf file://ntpd file://ntpdate"

# The ac_cv_header_readline_history is to stop ntpdc depending on either
# readline or curses
EXTRA_OECONF += "ac_cv_header_readline_history_h=no"

RECIPE_FLAGS += "ssl"
EXTRA_OECONF += "${EXTRA_OECONF_SSL}"
EXTRA_OECONF_SSL = "--without-openssl"
EXTRA_OECONF_SSL:USE_ssl = "--with-openssl"
DEPENDS:>USE_ssl = " libssl"

RECIPE_FLAGS += "crypto"
EXTRA_OECONF += "${EXTRA_OECONF_CRYPTO}"
EXTRA_OECONF_CRYPTO = "--without-crypto"
EXTRA_OECONF_CRYPTO:USE_crypto = "--with-crypto"
DEPENDS:>USE_crypto = " libcrypto"

CFLAGS += " -DPTYS_ARE_GETPT -DPTYS_ARE_SEARCHED"

do_autoreconf[prefuncs] =+ "do_autoreconf_pre"
do_autoreconf_pre() {
    sed -i -e 's:dist_man_MANS=	sntp.1::g' sntp/Makefile.am
}

do_install[postfuncs] =+ "do_install_extra_files"
do_install_extra_files() {
    install -d ${D}/${sysconfdir}
    install -m 644 ${SRCDIR}/ntp.conf ${D}/${sysconfdir}
    install -d ${D}/${sysconfdir}/network/if-up.d
    install -m 755 ${SRCDIR}/ntpdate ${D}/${sysconfdir}/network/if-up.d
    install -d ${D}/${sysconfdir}/init.d
    install -m 755 ${SRCDIR}/ntpd ${D}/${sysconfdir}/init.d/ntpd
}

inherit sysvinit
RECIPE_FLAGS += "ntpd_sysvinit_start ntpd_sysvinit_stop"
SYSVINIT_SCRIPT_ntpd = "ntpd"
DEFAULT_USE_ntpd_sysvinit_start	= "25"
DEFAULT_USE_ntpd_sysvinit_stop	= "25"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "ntpd ntpdate ntp-wait ntp-keygen sntp ntpq ntpdc \
    ntptime ntptrace tickadj"

# NOTE: you don't need ntpdate if you have ntpd ("ntpdc -q -g -x")

RDEPENDS_${PN}-ntpd = "libm"
RDEPENDS_${PN}-sntp = "libm"

FILES_${PN}-ntpd = "${sysconfdir}/ntp.conf \
    ${sysconfdir}/init.d/ntpd ${sysconfdir}/rc?.d/???ntpd"

FILES_${PN}-ntpdate = "${sysconfdir}/network/if-up.d/ntpdate"

# ntp originally includes tickadj. It's split off for inclusion in
# small firmware images on platforms with wonky clocks (e.g. OpenSlug)
RDEPENDS_${PN}-ntpd = "${PN}-tickadj"
