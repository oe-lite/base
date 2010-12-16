DESCRIPTION = "Libcap is a library for getting and setting POSIX.1e (formerly POSIX 6) draft 15 capabilities."
LICENSE = "GPL,BSD"

DEPENDS = "bison-native flex-native libattr"

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/pub/linux/libs/security/linux-privs/libcap2/libcap-${PV}.tar.bz2"

SRC_URI += "file://make.patch;patch=1"

S = "${WORKDIR}/libcap-${PV}"

BUILD_CFLAGS += "-I${S}/libcap/include"

do_install() {
        oe_runmake 'DESTDIR=${D}' lib=${libdir} install
}

RDEPENDS_${PN} = "libattr${RE}"

PACKAGES =+ "${PN}-capsh"
FILES_${PN}-capsh = "${base_sbindir}/capsh"
RDEPENDS_${PN}-capsh = "${PN}"
RPROVIDES_${PN}-capsh = "util/capsh"

PACKAGES =+ "${PN}-getcap"
FILES_${PN}-getcap = "${base_sbindir}/getcap"
RDEPENDS_${PN}-getcap = "${PN}"
RPROVIDES_${PN}-getcap = "util/getcap"

PACKAGES =+ "${PN}-getpcaps"
FILES_${PN}-getpcaps = "${base_sbindir}/getpcaps"
RDEPENDS_${PN}-getpcaps = "${PN}"
RPROVIDES_${PN}-getpcaps = "util/getpcaps"

PACKAGES =+ "${PN}-setcap"
FILES_${PN}-setcap = "${base_sbindir}/setcap"
RDEPENDS_${PN}-setcap = "${PN}"
RPROVIDES_${PN}-setcap = "util/setcap"
