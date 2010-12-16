DESCRIPTION = "Tools for managing memory technology devices."
HOMEPAGE = "http://www.linux-mtd.infradead.org/"
LICENSE = "GPLv2"
SECTION = "base"

BBCLASSEXTEND = "native"

DEPENDS = "zlib${RE}-dev lzo${RE}-dev libuuid${RE}"
PACKAGES =+ "${PN}-mkfs ${PN}-ubi ${PN}-core"

FILES_${PN}-mkfs = "${sbindir}/mkfs.* ${sbindir}/ubinize ${sbindir}/unubi ${sbindir}/jffs2dump"
FILES_${PN}-core = "${sbindir}/mtdinfo ${sbindir}/flashcp"
FILES_${PN}-ubi = "${sbindir}/ubiattach ${sbindir}/ubidetach \
    ${sbindir}/ubiformat ${sbindir}/ubimirror ${sbindir}/ubimkvol \
    ${sbindir}/ubinfo ${sbindir}/ubirename ${sbindir}/ubirmvol \
    ${sbindir}/ubirsvol ${sbindir}/ubiupdatevol"

RDEPENDS_${PN}-mkfs = "lzo zlib"
RDEPENDS_${PN} = "${PN}-mkfs ${PN}-ubi ${PN}-core"

SRC_URI = "git://git.infradead.org/mtd-utils.git;protocol=git;tag=v1.3.1 \
	   file://makefile-dir-layout-override.patch;patch=1"

S = "${WORKDIR}/git/"

EXTRA_OEMAKE = "'LDFLAGS=${LDFLAGS}' 'CFLAGS=${CFLAGS} -I${S}/include -DWITHOUT_XATTR'"
EXTRA_OEMAKE_append_recipe-native += "'PREFIX=${prefix}' 'SBINDIR=${bindir}'"

do_install () {
	oe_runmake install DESTDIR=${D}
	install -d ${D}${includedir}/mtd/
	for f in ${S}/include/mtd/*.h; do
		install -m 0644 $f ${D}${includedir}/mtd/
	done
}

PARALLEL_MAKE = ""
