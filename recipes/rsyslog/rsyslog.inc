DESCRIPTION = "Rsyslog is an enhanced multi-threaded syslogd"
DEPENDS = "libz libpthread libdl librt"
HOMEPAGE = "http://www.rsyslog.com/"
LICENSE = "GPL-3.0"

RDEPENDS_${PN} += "libz libpthread libdl librt"

SRC_URI = "http://www.rsyslog.com/files/download/rsyslog/${PN}-${PV}.tar.gz \
          file://rsyslog.conf \
          file://rsyslog"

inherit autotools-autoreconf sysvinit
RECIPE_FLAGS = "rsyslog_sysvinit_start"
DEFAULT_USE_rsyslog_sysvinit_start = "20"
do_install[postfuncs] =+ "do_install_conf"
do_install_conf() {
	sysvinit_install_script ${SRCDIR}/${PN}
	install ${SRCDIR}/rsyslog.conf ${D}${sysconfdir}/rsyslog.conf
}

CONFFILES_${PN} = "${sysconfdir}/rsyslog.conf"
FILES_${PN} += "${base_libdir}/systemd ${sysconfdir}/rsyslog.conf"
