DESCRIPTION = "Secure ftp daemon"
SECTION = "console/network"
LICENSE = "GPL"
PR = "r0"

DEPENDS += "${HOST_ARCH}/sysroot-libcrypt"
RDEPENDS_${PN} += "${HOST_ARCH}/sysroot-libcrypt"

inherit sysvinit
EXTRA_OEMAKE="-e SBINDIR=${D}${sbindir} MANDIR=${D}${mandir} LIBS=-lcrypt LINK="

SRC_URI = "ftp://vsftpd.beasts.org/users/cevans/vsftpd-${PV}.tar.gz \
	file://vsftpd.sh \
	file://vsftpd-default \
	file://nopam.patch;patch=1 \
	file://makefile.patch;patch=1 \
	file://vsftpd.conf"

RECIPE_OPTIONS = "vsftpd_sysvinit_start"
DEFAULT_CONFIG_vsftpd_sysvinit_start = "61"
SYSVINIT_SCRIPT_vsftpd = "vsftpd.sh"

do_configure() {
	# Fix hardcoded /usr, /etc, /var mess.
	cat tunables.c|sed s:\"/usr:\"${prefix}:g \
	    |sed s:\"/var:\"${localstatedir}:g \
	    |sed s:\"/etc:\"${sysconfdir}:g > tunables.c.new
	mv tunables.c.new tunables.c
}

do_compile() {
	oe_runmake
}

do_install() {
	oe_runmake install
	install -d -m 0555 ${D}${localstatedir}/share/empty
	install -D -m 0644 ${WORKDIR}/vsftpd.conf ${D}${sysconfdir}/vsftpd.conf
	install -D -m 644 ${WORKDIR}/vsftpd-default ${D}${sysconfdir}/default/vsftpd
}

do_install_append_RECIPE_OPTION_sysvinit () {
	sysvinit_install_script ${WORKDIR}/vsftpd.sh
}
