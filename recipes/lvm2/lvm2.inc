DESCRIPTION = "LVM2 refers to the userspace toolset that provide logical volume management facilities on linux"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "ftp://sources.redhat.com/pub/${PN}/LVM2.${PV}.tgz"
S = "${SRCDIR}/LVM2.${PV}"

inherit autotools auto-package-libs auto-package-utils pkgconfig

AUTO_PACKAGE_UTILS = """
	blkdeactivate
	dmsetup
	fsadm
	lvmconf
	lvmdump
	vgimportclone
	lvm
"""

FILES_${PN}-lvm += "${sbindir}"

AUTO_PACKAGE_UTILS_RDEPENDS += "${PN}"
RDEPENDS_${PN}-dmsetup += "libdevmapper"
RDEPENDS_${PN}-lvm += "libdevmapper"

PACKAGES += "${PN}-all"
RDEPENDS_${PN}-all = "${AUTO_PACKAGE_UTILS_PACKAGES} ${LIBS_AUTO_RPACKAGES}"

AUTO_PACKAGE_LIBS = "devmapper"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
