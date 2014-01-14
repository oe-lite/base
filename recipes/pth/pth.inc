SUMMARY = "GNU Portable Threads library"
HOMEPAGE = "http://www.gnu.org/software/pth/"
LICENSE = "GPLv2+"

inherit autotools pkgconfig library auto-package-utils binconfig

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/pth/pth-${PV}.tar.gz"
SRC_URI += "file://fix_for_3x_kernels.patch"
SRC_URI += "file://pth-add-pkgconfig-support.patch"

PARALLEL_MAKE = ""

# pth.pc is added locally and thus installed here
do_install[postfuncs] += "do_install_pc"
do_install_pc() {
	install -d ${D}/${libdir}/pkgconfig
	install -m 0644 ${S}/pth.pc ${D}/${libdir}/pkgconfig/
}

AUTO_PACKAGE_UTILS += "pth-config"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"

