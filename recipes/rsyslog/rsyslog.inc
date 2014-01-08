DESCRIPTION = "Rsyslog is an enhanced multi-threaded syslogd"
HOMEPAGE = "http://www.rsyslog.com/"
LICENSE = "GPL-3.0"

DEPENDS_LIBC = "libdl libpthread librt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS = "libz libuuid ${DEPENDS_LIBC}"
DEPENDS_${PN} += "libz libuuid ${DEPENDS_LIBC}"
RDEPENDS_${PN} += "libz libuuid ${DEPENDS_LIBC}"

SRC_URI = "http://www.rsyslog.com/files/download/rsyslog/${PN}-${PV}.tar.gz \
          file://rsyslog.conf \
          file://rsyslog"

inherit autotools-autoreconf sysvinit pkgconfig

EXTRA_OECONF += "--enable-cached-man-pages"

RECIPE_FLAGS = "rsyslog_sysvinit_start rsyslog_logdir rsyslog_logfile"
DEFAULT_USE_rsyslog_sysvinit_start = "20"
DEFAULT_USE_rsyslog_logdir = "${localstatedir}/log"
DEFAULT_USE_rsyslog_logfile = "messages"
do_install[postfuncs] =+ "do_install_conf"
do_install_conf() {
	sysvinit_install_script ${SRCDIR}/${PN}

	if [ -n "${USE_rsyslog_logfile}" ]; then
		sed 's#/var/log/messages#/var/log/${USE_rsyslog_logfile}#' \
			-i ${SRCDIR}/rsyslog.conf
	fi

	if [ -n "${USE_rsyslog_logdir}" ]; then
		sed 's#/var/log#${USE_rsyslog_logdir}#' \
			-i ${SRCDIR}/rsyslog.conf
	fi

	install ${SRCDIR}/rsyslog.conf ${D}${sysconfdir}/rsyslog.conf
}

PACKAGES =+ "${PN}-conf"

FILES_${PN}-dev += "${libdir}/${PN}/*.la"
FILES_${PN} += "${base_libdir}/systemd"
FILES_${PN}-conf += "${sysconfdir}/rsyslog.conf"

RDEPENDS_${PN} += "${PN}-conf"
