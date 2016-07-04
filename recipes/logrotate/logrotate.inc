DESCRIPTION = "The logrotate utility is designed to simplify \
							the administration of log files on a system which \
							generates a lot of log files."

HOMEPAGE = "https://github.com/logrotate/logrotate"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "https://github.com/logrotate/logrotate/archive/${PV}.tar.gz"

DEPENDS =+ "libpopt"

inherit autotools-autoreconf

EXTRA_OECONF += "--with-acl=no --with-selinux=no"

# touch missing files to satisfy autoreconf
do_autoreconf[prefuncs] =+ "do_autoreconf_prepare"
do_autoreconf_prepare() {
	touch ${S}/NEWS
	touch ${S}/README
	touch ${S}/AUTHORS
	touch ${S}/ChangeLog
}

do_install[postfuncs] =+ "do_install_conf"
do_install_conf() {
	install -d ${D}${sysconfdir}
	install -m 0644 ${B}/examples/logrotate-default ${D}${sysconfdir}/logrotate.conf
}

PACKAGES =+ "${PN}-conf"

FILES_${PN}-conf += "${sysconfdir}/logrotate.conf"

RDEPENDS_${PN} += "${PN}-conf libc libpopt"
DEPENDS_${PN} += "${PN}-conf libc libpopt"
