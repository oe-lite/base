DESCRIPTION = "Base system password/group files."
SECTION = "base"
PR = "r1"
LICENSE = "GPL"

SRC_URI = "${DEBIAN_MIRROR}/main/b/base-passwd/base-passwd_${PV}.tar.gz"

S = "${WORKDIR}/base-passwd"

do_install () {
	install -D -p -m 644 passwd.master \
		${D}${sysconfdir}/passwd
	install -D -p -m 644 group.master \
		${D}${sysconfdir}/group
}

do_install_append () {
	sed -i 's#^root:.*#root:$1$roLh0nu9$eOcbErcvq7K9sJxLIuMwS1:0:0:root:/:/bin/sh#g' ${D}${sysconfdir}/passwd
}
