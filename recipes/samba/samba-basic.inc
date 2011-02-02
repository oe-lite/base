EXTRA_OECONF += "\
    --without-ads \
    --without-winbind \
    --without-ldap \
    --without-krb5"

PACKAGES =+ "libsmbclient libsmbclient-dev cifs cifs-doc swat"

FILES_cifs = "${base_sbindir}/mount.cifs ${base_sbindir}/umount.cifs"
FILES_cifs-doc = "${mandir}/man8/mount.cifs.8 ${mandir}/man8/umount.cifs.8"
FILES_libsmbclient = "${libdir}/libsmbclient.so.*"
FILES_libsmbclient-dev = "${libdir}/libsmbclient.so ${includedir}"
FILES_swat       = "${sbindir}/swat ${datadir}/swat ${libdir}/*.msg"
