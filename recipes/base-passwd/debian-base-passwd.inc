DESCRIPTION = "Base system password/group files."

DEFAULT_PREFERENCE = "-1"

require conf/fetch/debian.conf
SRC_URI = "${DEBIAN_MIRROR}/main/b/base-passwd/base-passwd_${PV}.tar.gz"
S = "${SRCDIR}/base-passwd"

do_install () {
	install -D -p -m 644 passwd.master ${D}${sysconfdir}/passwd
	install -D -p -m 644 group.master ${D}${sysconfdir}/group
}

require root-password.inc

PACKAGES = "${PN}"
PROVIDES_${PN} = "base-passwd"
