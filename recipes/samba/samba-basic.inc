EXTRA_OECONF += "\
    --without-ads \
    --without-winbind \
    --without-ldap \
    --without-krb5"

PACKAGES =+ "${PN}-cifs ${PN}-cifs-doc ${PN}-swat"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "smbclient smbsharemodes tdb netapi"
AUTO_PACKAGE_LIBS_DEV_DEPENDS += "libc"
AUTO_PACKAGE_LIBS_RDEPENDS += "libc"
DEPENDS_${PN}-libsmbclient += "libdl libresolv libpthread libtdb"
RDEPENDS_${PN}-libsmbclient += "libdl libresolv libpthread libtdb"
DEPENDS_${PN}-libsmbsharemodes += "libdl libresolv libtdb"
RDEPENDS_${PN}-libsmbsharemodes += "libdl libresolv libtdb"
DEPENDS_${PN}-libnetapi += "libdl libresolv libtdb"
RDEPENDS_${PN}-libnetapi += "libdl libresolv libtdb"

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
DEPENDS_${PN}-eventlogadm += "libtdb"
RDEPENDS_${PN}-eventlogadm += "libtdb"
DEPENDS_${PN}-ldbrename += "libtdb"
RDEPENDS_${PN}-ldbrename += "libtdb"
DEPENDS_${PN}-nmblookup += "libtdb"
RDEPENDS_${PN}-nmblookup += "libtdb"
DEPENDS_${PN}-profiles += "libtdb"
RDEPENDS_${PN}-profiles += "libtdb"
DEPENDS_${PN}-smbcacls += "libtdb"
RDEPENDS_${PN}-smbcacls += "libtdb"
DEPENDS_${PN}-smbcquotas += "libtdb"
RDEPENDS_${PN}-smbcquotas += "libtdb"
DEPENDS_${PN}-smbspool += "libtdb"
RDEPENDS_${PN}-smbspool += "libtdb"
DEPENDS_${PN}-smbtree += "libtdb"
RDEPENDS_${PN}-smbtree += "libtdb"
DEPENDS_${PN}-tdbtool += "libtdb"
RDEPENDS_${PN}-tdbtool += "libtdb"
DEPENDS_${PN}-ntlm-auth += "libtdb"
RDEPENDS_${PN}-ntlm-auth += "libtdb"
DEPENDS_${PN}-rpcclient += "libtdb"
RDEPENDS_${PN}-rpcclient += "libtdb"
DEPENDS_${PN}-smbclient += "libtdb"
RDEPENDS_${PN}-smbclient += "libtdb"
DEPENDS_${PN}-smbget += "libtdb"
RDEPENDS_${PN}-smbget += "libtdb"
DEPENDS_${PN}-smbstatus += "libtdb"
RDEPENDS_${PN}-smbstatus += "libtdb"
DEPENDS_${PN}-tdbbackup += "libtdb"
RDEPENDS_${PN}-tdbbackup += "libtdb"
DEPENDS_${PN}-testparm += "libtdb"
RDEPENDS_${PN}-testparm += "libtdb"
DEPENDS_${PN}-net += "libtdb"
RDEPENDS_${PN}-net += "libtdb"
DEPENDS_${PN}-pdbedit += "libtdb"
RDEPENDS_${PN}-pdbedit += "libtdb"
DEPENDS_${PN}-sharesec += "libtdb"
RDEPENDS_${PN}-sharesec += "libtdb"
DEPENDS_${PN}-smbcontrol += "libtdb"
RDEPENDS_${PN}-smbcontrol += "libtdb"
DEPENDS_${PN}-smbpasswd += "libtdb"
RDEPENDS_${PN}-smbpasswd += "libtdb"
DEPENDS_${PN}-tdbdump += "libtdb"
RDEPENDS_${PN}-tdbdump += "libtdb"
DEPENDS_${PN}-nmbd += "libtdb"
RDEPENDS_${PN}-nmbd += "libtdb"
DEPENDS_${PN}-smbd += "libtdb libcrypt"
RDEPENDS_${PN}-smbd += "libtdb libcrypt"

DEPENDS_${PN}-swat += "libc libcrypt libdl libresolv libtdb"
RDEPENDS_${PN}-swat += "libc libcrypt libdl libresolv libtdb"

FILES_${PN}-cifs = "${base_sbindir}/mount.cifs ${base_sbindir}/umount.cifs"
FILES_${PN}-cifs-doc = "${mandir}/man8/mount.cifs.8 ${mandir}/man8/umount.cifs.8"
FILES_${PN}-swat = "${sbindir}/swat ${datadir}/swat ${libdir}/*.msg"

#To be removed in next base master release!
PROVIDES_${PN}-cifs += "cifs"
PROVIDES_${PN}-cifs-doc += "cifs-doc"
PROVIDES_${PN}-swat += "swat"
