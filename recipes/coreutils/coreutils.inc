DESCRIPTION = "The GNU Core Utilities provide the basic file, shell and text \
manipulation utilities. These are the core utilities which are expected to exist on \
every system."
LICENSE = "GPL-3.0+"

COMPATIBLE_HOST_ARCHS = ".*linux"

RECIPE_TYPES = "native machine"

inherit autotools gettext pkgconfig

require conf/fetch/gnu.conf

SRC_URI = "${GNU_MIRROR}/${PN}/${PN}-${PV}.tar.xz"

RECIPE_FLAGS += "singlebin"
EXTRA_OECONF:>machine += " --libexecdir=${libdir} --enable-install-program=arch ${EXTRA_OECONF_SINGLEBIN}"
EXTRA_OECONF_SINGLEBIN = ""
EXTRA_OECONF_SINGLEBIN:USE_singlebin = "--enable-single-binary"

EXTRA_OECONF:>native += " --without-gmp"
EXTRA_OECONF:>sdk += " --enable-install-program=arch"

DEPENDS += "gettext libpthread libgmp libcap"

RECIPE_FLAGS += "ssl"
EXTRA_OECONF += "${EXTRA_OECONF_SSL}"
EXTRA_OECONF_SSL = "--without-openssl"
EXTRA_OECONF_SSL:USE_ssl = "--with-openssl=yes"
DEPENDS:>USE_ssl = " libssl"

inherit auto-package-utils

AUTO_PACKAGE_UTILS = "chown dd expr install mkfifo od readlink sha384sum stty tr uptime \
		 arch chroot df factor join mknod paste realpath sha512sum sum true users \
		 base32 cksum dir false kill mktemp pathchk rm shred sync truncate vdir \
		 base64 comm dircolors fmt link mv pinky rmdir shuf tac tsort wc \
		 basename dirname fold ln nice pr runcon sleep tail tty who \
		 cat cp du groups logname nl printenv seq sort tee uname whoami \
		 chcon csplit echo head ls nohup printf sha1sum split test unexpand yes \
		 chgrp cut env hostid md5sum nproc ptx sha224sum stat timeout uniq \
		 chmod date expand id mkdir numfmt pwd sha256sum stdbuf touch unlink"

AUTO_PACKAGE_UTILS_RDEPENDS:>USE_singlebin += "${PN}"

REPENDS_SINGLEBIN = "${AUTO_PACKAGE_UTILS_PACKAGES}"
REPENDS_SINGLEBIN:USE_singlebin = ""
DEPENDS_${PN} += " libc libcap libgmp libiconv"
RDEPENDS_${PN} += "${REPENDS_SINGLEBIN} libc libcap libgmp libiconv"

FILES_${PN}-test += "${bindir}/["
