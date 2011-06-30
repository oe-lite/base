DESCRIPTION = "Base system password/group files."
LICENSE = "GPL"

RECIPE_FLAGS = "passwd_root"
DEFAULT_USE_passwd_root = "$1$L9mzJfTZ$2ED5as2K2yZ98CN/BQuy1."

require conf/fetch/debian.conf
SRC_URI = "${DEBIAN_MIRROR}/main/b/base-passwd/base-passwd_${PV}.tar.gz"

S = "${SRCDIR}/${PN}"

do_install () {
	install -D -p -m 644 passwd.master \
		${D}${sysconfdir}/passwd
	install -D -p -m 644 group.master \
		${D}${sysconfdir}/group
}

do_install[postfuncs] += "do_install_root_passwd"
do_install_root_passwd () {
	sed -i 's#^root:.*#root:${USE_passwd_root}:0:0:root:/root:/bin/sh#g' ${D}${sysconfdir}/passwd
}
