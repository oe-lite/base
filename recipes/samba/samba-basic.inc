EXTRA_OECONF += "\
    --without-ads \
    --without-winbind \
    --without-ldap \
    --without-krb5"

PACKAGES =+ "${PN}-cifs ${PN}-cifs-doc ${PN}-swat"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "smbclient smbsharemodes tdb tevent netapi"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc"
DEPENDS_${PN}-libsmbclient += "libdl libresolv libpthread libtdb libtevent"
RDEPENDS_${PN}-libsmbclient += "libdl libresolv libpthread libtdb libtevent"
DEPENDS_${PN}-libsmbsharemodes += "libdl libresolv libtdb"
RDEPENDS_${PN}-libsmbsharemodes += "libdl libresolv libtdb"
DEPENDS_${PN}-libnetapi += "libdl libresolv libtdb libtevent"
RDEPENDS_${PN}-libnetapi += "libdl libresolv libtdb libtevent"

inherit auto-package-utils

AUTO_PACKAGE_UTILS_DEPENDS += "libresolv libdl libc"
AUTO_PACKAGE_UTILS_RDEPENDS += "libresolv libdl libc"
AUTO_PACKAGE_UTILS = "\
eventlogadm ldbdel ldbrename nmblookup profiles \
smbcacls smbcquotas smbspool smbtree tdbtool \
findsmb ldbedit ldbsearch ntlm_auth rpcclient \
smbclient smbget smbstatus tdbbackup testparm \
ldbadd ldbmodify net pdbedit sharesec \
smbcontrol smbpasswd smbtar tdbdump \
nmbd smbd \
"
DEPENDS_${PN}-eventlogadm += "libtdb libtevent"
RDEPENDS_${PN}-eventlogadm += "libtdb libtevent"
DEPENDS_${PN}-ldbrename += "libtdb libtevent"
RDEPENDS_${PN}-ldbrename += "libtdb libtevent"
DEPENDS_${PN}-nmblookup += "libtdb libtevent"
RDEPENDS_${PN}-nmblookup += "libtdb libtevent"
DEPENDS_${PN}-profiles += "libtdb libtevent"
RDEPENDS_${PN}-profiles += "libtdb libtevent"
DEPENDS_${PN}-smbcacls += "libtdb libtevent"
RDEPENDS_${PN}-smbcacls += "libtdb libtevent"
DEPENDS_${PN}-smbcquotas += "libtdb libtevent"
RDEPENDS_${PN}-smbcquotas += "libtdb libtevent"
DEPENDS_${PN}-smbspool += "libtdb libtevent"
RDEPENDS_${PN}-smbspool += "libtdb libtevent"
DEPENDS_${PN}-smbtree += "libtdb libtevent"
RDEPENDS_${PN}-smbtree += "libtdb libtevent"
DEPENDS_${PN}-tdbtool += "libtdb"
RDEPENDS_${PN}-tdbtool += "libtdb"
DEPENDS_${PN}-ntlm-auth += "libtdb libtevent"
RDEPENDS_${PN}-ntlm-auth += "libtdb libtevent"
DEPENDS_${PN}-rpcclient += "libtdb libtevent"
RDEPENDS_${PN}-rpcclient += "libtdb libtevent"
DEPENDS_${PN}-smbclient += "libtdb libtevent"
RDEPENDS_${PN}-smbclient += "libtdb libtevent"
DEPENDS_${PN}-smbget += "libtdb libtevent"
RDEPENDS_${PN}-smbget += "libtdb libtevent"
DEPENDS_${PN}-smbstatus += "libtdb libtevent"
RDEPENDS_${PN}-smbstatus += "libtdb libtevent"
DEPENDS_${PN}-tdbbackup += "libtdb"
RDEPENDS_${PN}-tdbbackup += "libtdb"
DEPENDS_${PN}-testparm += "libtdb libtevent"
RDEPENDS_${PN}-testparm += "libtdb libtevent"
DEPENDS_${PN}-net += "libtdb libtevent"
RDEPENDS_${PN}-net += "libtdb libtevent"
DEPENDS_${PN}-pdbedit += "libtdb libtevent"
RDEPENDS_${PN}-pdbedit += "libtdb libtevent"
DEPENDS_${PN}-sharesec += "libtdb libtevent"
RDEPENDS_${PN}-sharesec += "libtdb libtevent"
DEPENDS_${PN}-smbcontrol += "libtdb libtevent"
RDEPENDS_${PN}-smbcontrol += "libtdb libtevent"
DEPENDS_${PN}-smbpasswd += "libtdb libtevent"
RDEPENDS_${PN}-smbpasswd += "libtdb libtevent"
DEPENDS_${PN}-tdbdump += "libtdb"
RDEPENDS_${PN}-tdbdump += "libtdb"
DEPENDS_${PN}-nmbd += "libtdb libtevent"
RDEPENDS_${PN}-nmbd += "libtdb libtevent"
DEPENDS_${PN}-smbd += "libtdb libtevent libcrypt"
RDEPENDS_${PN}-smbd += "libtdb libtevent libcrypt"

DEPENDS_${PN}-swat += "libc libcrypt libdl libresolv libtdb libtevent"
RDEPENDS_${PN}-swat += "libc libcrypt libdl libresolv libtdb libtevent"

FILES_${PN}-cifs = "${base_sbindir}/mount.cifs ${base_sbindir}/umount.cifs"
FILES_${PN}-cifs-doc = "${mandir}/man8/mount.cifs.8 ${mandir}/man8/umount.cifs.8"
FILES_${PN}-swat = "${sbindir}/swat ${datadir}/swat ${libdir}/*.msg"
