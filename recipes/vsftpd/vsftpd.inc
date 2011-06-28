DESCRIPTION = "Secure ftp daemon"
LICENSE = "GPL"

inherit sysvinit

SRC_URI = "ftp://vsftpd.beasts.org/users/cevans/vsftpd-${PV}.tar.gz \
    file://init \
    file://vsftpd.conf"

DEPENDS = "${HOST_ARCH}/sysroot-libcrypt \
    ${HOST_ARCH}/sysroot-libnsl ${HOST_ARCH}/sysroot-libresolv"

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

    # Configure CFLAGS and hardcode LIBS
    mv Makefile.new Makefile
    cat Makefile \
        | sed -e 's:^\(CFLAGS.*=\).*:\1 ${CFLAGS}:g' \
        | sed -e 's:^\(LIBS.*=\).*:\1 -lnsl -lresolv -lcrypt:g' \
        > Makefile.new
    mv Makefile.new Makefile
}

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${sbindir}
    install -d ${D}${mandir}/man8
    install -d ${D}${mandir}/man5
    oe_runmake 'DESTDIR=${D}' install
    install -d ${D}${sysconfdir}
    install -m 0755 ${SRCDIR}/vsftpd.conf ${D}${sysconfdir}/vsftpd.conf
    install -d ${D}${sysconfdir}/init.d/
    install -m 755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/vsftpd
}

RECIPE_OPTIONS += "vsftpd_sysvinit_start vsftpd_sysvinit_stop"
DEFAULT_CONFIG_vsftpd_sysvinit_start	= "20"
DEFAULT_CONFIG_vsftpd_sysvinit_stop	= "20"

RDEPENDS_${PN} = "${HOST_ARCH}/sysroot-libcrypt \
    ${HOST_ARCH}/sysroot-libnsl ${HOST_ARCH}/sysroot-libresolv"

# FIXME: do something else!
#pkg_postinst() {
#    if [ "x$D" != "x" ]; then
#        exit 1
#    fi
#    addgroup ftp
#    adduser --system --home /var/lib/ftp --no-create-home --ingroup ftp --disabled-password -s /bin/false ftp
#    mkdir -p ${localstatedir}/share/empty
#}
