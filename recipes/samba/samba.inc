# -*- mode:python; -*-
SUMMARY = "Samba is the standard Windows interoperability suite of programs for Linux and Unix"
DESCRIPTION = """Samba provides secure, stable and fast file and print
services for all clients using the SMB/CIFS protocol, such as all
versions of DOS and Windows, OS/2, Linux and many others. Samba is an
important component to seamlessly integrate Linux/Unix Servers and
Desktops into Active Directory environments using the winbind
daemon."""

DEPENDS = "libreadline \
           libiconv \
           libdl \
           libresolv \
           libpthread \
           libcrypt"

SRC_URI = "http://samba.org/samba/ftp/stable/samba-${PV}.tar.gz \
           file://volatiles.03_samba \
           file://smb.conf \
           file://init \
           file://tdb.pc \
           "

S = "${SRCDIR}/samba-${PV}/source"

inherit autotools sysvinit

SRC_URI += "file://config.site"
SRC_HOST_SITEFILES = "${SRCDIR}/config.site"

FILES_${PN}     += "${libdir}/vfs/*.so ${libdir}/charset/*.so ${libdir}/*.dat \
                    ${libdir}/auth/*.so ${libdir}/security/*.so"
FILES_${PN}-dbg += "${libdir}/vfs/.debug/*.so ${libdir}/charset/.debug/*.so \
                    ${libdir}/auth/.debug/*.so ${libdir}/security/.debug/*.so"

RDEPENDS_${PN} += "libcrypt libresolv"

SAMBAMMAP = "no"
SAMBAMMAP_libc-glibc = "yes"

# The file system settings --foodir=dirfoo and overridden unconditionally
# in the samba config by --with-foodir=dirfoo - even if the --with is not
# specified!  Fix that here.  Set the privatedir to /etc/samba/private.
EXTRA_OECONF='--disable-cups \
              --with-readline=${STAGE_DIR}${libdir}/.. \
              --with-libiconv=${STAGE_DIR}${libdir}/.. \
              --without-automount \
              --with-configdir=${sysconfdir}/samba \
              --with-privatedir=${sysconfdir}/samba/private \
              --with-lockdir=${localstatedir}/lock \
              --with-piddir=${localstatedir}/run \
              --with-logfilebase=${localstatedir}/log \
              --with-libdir=${libdir} \
              --with-mandir=${mandir} \
              --with-swatdir=${datadir}/swat \
              --with-aio-support \
              --without-libtalloc \
              samba_cv_struct_timespec=yes \
              libreplace_cv_HAVE_MMAP=${SAMBAMMAP}'

RECIPE_FLAGS += "samba_sysvinit_start samba_sysvinit_stop"
SYSVINIT_SCRIPT_samba = "samba"
DEFAULT_USE_samba_sysvinit_start = "20"
DEFAULT_USE_samba_sysvinit_stop = "20"

# No dependencies, goes in at level 20 (NOTE: take care with the
# level, later levels put the shutdown later too - see the links
# in rc6.d, the shutdown must precede network shutdown).
CONFFILES_${PN} = "${sysconfdir}/samba/smb.conf"

do_configure[prefuncs] += "do_configure_pre"
do_configure_pre () {
	./script/mkversion.sh
	if [ ! -e acinclude.m4 ]; then
		touch aclocal.m4	
		cat aclocal.m4 > acinclude.m4
	fi
}

do_install[postfuncs] += "do_install_extra"
do_install_extra() {
	install -d ${D}${libdir}/pkgconfig/
	cp ${SRCDIR}/tdb.pc ${D}${libdir}/pkgconfig/
	mv ${D}${libdir}/libsmbclient.so ${D}${libdir}/libsmbclient.so.0 || true
	ln -sf libsmbclient.so.0 ${D}${libdir}/libsmbclient.so
	mkdir -p ${D}${base_sbindir}
	rm -f ${D}${bindir}/*.old
	rm -f ${D}${sbindir}/*.old
	[ -f ${D}${sbindir}/mount.cifs ] && mv ${D}${sbindir}/mount.cifs ${D}${base_sbindir}/
	[ -f ${D}${sbindir}/umount.cifs ] && mv ${D}${sbindir}/umount.cifs ${D}${base_sbindir}/

	# This is needed for < 3.2.4
	rm -f ${D}${sbindir}/mount.smbfs ${D}${base_sbindir}/mount.smbfs
	if [ -f ${D}${bindir}/smbmount ]; then
		ln -sf ${bindir}/smbmount ${D}${base_sbindir}/mount.smb
		ln -sf ${bindir}/smbmount ${D}${base_sbindir}/mount.smbfs
	fi
	
	install -D -m 755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/samba
	install -D -m 644 ${SRCDIR}/smb.conf ${D}${sysconfdir}/samba/smb.conf
	install -D -m 644 ${SRCDIR}/volatiles.03_samba ${D}${sysconfdir}/default/volatiles/volatiles.03_samba
	install -d ${D}/var/log/samba
	install -d ${D}/var/spool/samba
}
