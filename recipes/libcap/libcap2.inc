# -*- mode:python; -*-
DESCRIPTION = "Libcap is a library for getting and setting POSIX.1e \
	(formerly POSIX 6) draft 15 capabilities."
LICENSE = "GPL,BSD"

RECIPE_TYPES = "machine"

inherit make c library auto-package-utils

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_GIT}/linux/kernel/git/morgan/libcap.git"
S = "${SRCDIR}/libcap"

DEPENDS = "native:bison native:flex libattr"

BUILD_CFLAGS += "-I${S}/libcap/include"
EXTRA_OEMAKE = "PAM_CAP=no"

do_install() {
	oe_runmake DESTDIR="${D}" \
		prefix="${prefix}" exec_prefix="${exec_prefix}" \
		lib=`basename ${libdir}` \
		CC='${CC}' CFLAGS='${CFLAGS}' LDFLAGS='${LDFLAGS}' \
		BUILD_CC='${BUILD_CC}' BUILD_CFLAGS='${BUILD_CFLAGS}' \
		AR='${AR}' RANLIB='${RANLIB}' \
		RAISE_SETFCAP=no \
		install
}

DEPENDS_${PN} += "libattr"

AUTO_PACKAGE_UTILS = "capsh getcap getpcaps setcap"
AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}"
