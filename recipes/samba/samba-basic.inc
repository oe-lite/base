EXTRA_OECONF += "\
    --without-ads \
    --without-winbind \
    --without-ldap \
    --without-krb5"

PACKAGES =+ "libsmbclient libsmbclient-dev cifs cifs-doc swat"

inherit auto-package-utils

AUTO_PACKAGE_UTILS_RDEPENDS = "libresolv libdl libc"
AUTO_PACKAGE_UTILS = "\
eventlogadm ldbdel ldbrename nmblookup profiles \
smbcacls smbcquotas smbspool smbtree tdbtool \
findsmb ldbedit ldbsearch ntlm_auth rpcclient \
smbclient smbget smbstatus tdbbackup testparm \
ldbadd ldbmodify net pdbedit sharesec \
smbcontrol smbpasswd smbtar tdbdump \
 \
nmbd  smbd \
"
RDEPENDS_${PN}-smbd += "libcrypt"

RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PROVIDES}"

FILES_cifs = "${base_sbindir}/mount.cifs ${base_sbindir}/umount.cifs"
FILES_cifs-doc = "${mandir}/man8/mount.cifs.8 ${mandir}/man8/umount.cifs.8"
FILES_libsmbclient = "${libdir}/libsmbclient.so.*"
FILES_libsmbclient-dev = "${libdir}/libsmbclient.so ${includedir}"
FILES_swat       = "${sbindir}/swat ${datadir}/swat ${libdir}/*.msg"
