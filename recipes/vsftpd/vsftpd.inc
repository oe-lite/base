# -*- mode:python; -*-
DESCRIPTION = "Secure ftp daemon"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make sysvinit passwd

SRC_URI = "https://security.appspot.com/downloads/vsftpd-${PV}.tar.gz \
           file://0001-utmpx-builddef.patch \
           file://0003-fix-CVE-2015-1419.patch\
           file://allow-overwrite-cflags-etc.patch"
SRC_URI += "file://init file://vsftpd.conf file://passwd file://group"

DEPENDS_LIBC = "libcrypt libnsl libresolv"
DEPENDS_LIBC:HOST_LIBC_mingw = ""
DEPENDS_LIBC:HOST_LIBC_musl = "libcrypt libresolv"
DEPENDS = "${DEPENDS_LIBC}"

LIBS = "-lnsl -lresolv -lcrypt"
LIBS:HOST_LIBC_musl = "-lresolv -lcrypt"

#repect CFLAGS from upstream
CFLAGS += " -fPIE -fstack-protector --param=ssp-buffer-size=4"
LDFLAGS += " -fPIE -pie -Wl,-z,relro -Wl,-z,now"

do_configure() {
    # Fix hardcoded /usr, /etc, /var mess.
    cat tunables.c \
        | sed s:\"/usr:\"${prefix}:g \
        | sed s:\"/var:\"${localstatedir}:g \
        | sed s:\"${prefix}/share/empty:\"${localstatedir}/share/empty:g \
        | sed s:\"/etc:\"${sysconfdir}:g \
        > tunables.c.new
    mv tunables.c.new tunables.c
    cat Makefile \
        | sed 's: /usr/local/sbin: \$\(DESTDIR\)${sbindir}:g' \
        | sed 's: /usr/sbin: \$\(DESTDIR\)${sbindir}:g' \
        | sed 's: /usr/local/man: \$\(DESTDIR\)${mandir}:g' \
        | sed 's: /usr/share/man: \$\(DESTDIR\)${mandir}:g' \
        | sed 's: /usr/man: \$\(DESTDIR\)${mandir}:g' \
        | sed 's: /etc: \$\(DESTDIR\)${sysconfdir}:g' \
        | sed 's: /etc: \$\(DESTDIR\)${sysconfdir}:g' \
        > Makefile.new
    mv Makefile.new Makefile
}

DISABLE_UTMPX = ""
DISABLE_UTMPX:HOST_LIBC_musl = "do_configure_disable_utmpx"
do_configure[postfuncs] += "${DISABLE_UTMPX}"
do_configure_disable_utmpx() {
    cat builddefs.h \
        | sed 's/.*VSF_BUILD_UTMPX/#undef VSF_BUILD_UTMPX/' \
        > builddefs.h.new
    mv builddefs.h.new builddefs.h
}

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${sbindir}
    install -d ${D}${mandir}/man8
    install -d ${D}${mandir}/man5
    oe_runmake 'DESTDIR=${D}' install
    install -d ${D}/var/share/empty
    install -d ${D}${sysconfdir}
    install -m 0755 ${SRCDIR}/vsftpd.conf ${D}${sysconfdir}/vsftpd.conf
    install -d ${D}${sysconfdir}/init.d/
    install -m 755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/vsftpd
}

RECIPE_FLAGS += "ftp_home"
DEFAULT_USE_ftp_home = "/home/ftp"
do_configure[postfuncs] += "do_configure_set_ftp_home"
do_configure_set_ftp_home() {
	sed -i -e "s|PLACEHOLDER_FTP_HOME|${USE_ftp_home}|" \
		${SRCDIR}/passwd
}

RECIPE_FLAGS += "vsftpd_sysvinit_start vsftpd_sysvinit_stop"
DEFAULT_USE_vsftpd_sysvinit_start	= "20"
DEFAULT_USE_vsftpd_sysvinit_stop	= "20"

RDEPENDS_${PN} = "libcrypt libnsl libresolv libc"
FILES_${PN} += "/var/share/empty"

PACKAGES =+ "${PN}-config"
RDEPENDS_${PN} += "${PN}-config"
FILES_${PN}-config = "${sysconfdir}/vsftpd.conf"

PACKAGES =+ "${PN}-init"
RDEPENDS_${PN}:>USE_sysvinit += "${PN}-init"
FILES_${PN}-init = "${sysconfdir}/init.d ${sysconfdir}/rc?.d"

inherit s6rc
S6RC_LONGRUN_SERVICES = "vsftpd vsftpd-log"
SRC_URI += "file://vsftpd.run file://vsftpd-log.run file://vsftpd-log.notification-fd"
RECIPE_FLAGS += "vsftpd_s6rc_dependencies"
DEFAULT_USE_vsftpd_s6rc_dependencies = "vsftpd-log net"
PACKAGES += "${PN}-s6"
FILES_${PN}-s6 += "${s6rcsrcdir}"
RDEPENDS_${PN}:>USE_s6rc += " ${PN}-s6"

# FIXME: do something else!
#pkg_postinst() {
#    if [ "x$D" != "x" ]; then
#        exit 1
#    fi
#    addgroup ftp
#    adduser --system --home /var/lib/ftp --no-create-home --ingroup ftp --disabled-password -s /bin/false ftp
#    mkdir -p ${localstatedir}/share/empty
#}
