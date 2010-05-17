DESCRIPTION = "Tools for managing memory technology devices."
SECTION = "base"

#FIXME: Only mkfs.* and uuidd (UUID-generation daemon) depends on
#       util-linux-ng zlib and lzo (and libm.so). Not needed on
#       target.
DEPENDS = "zlib${RE}-dev lzo${RE}-dev util-linux-ng${RE}-dev"
PACKAGES =+ "${PN}-mkfs"
FILES_${PN}-mkfs = "${sbindir}/mkfs.*"

HOMEPAGE = "http://www.linux-mtd.infradead.org/"
LICENSE = "GPLv2"
PR = "r3"

SRC_URI = "git://git.infradead.org/mtd-utils.git;protocol=git;tag=v1.3.1"

S = "${WORKDIR}/git/"

EXTRA_OEMAKE = "'LDFLAGS=${LDFLAGS}' 'CFLAGS=${CFLAGS} -I${S}/include -DWITHOUT_XATTR'"

do_install () {
	oe_runmake install DESTDIR=${D}
	install -d ${D}${includedir}/mtd/
	for f in ${S}/include/mtd/*.h; do
		install -m 0644 $f ${D}${includedir}/mtd/
	done
}

PARALLEL_MAKE = ""

BBCLASSEXTEND = "native"
#NATIVE_INSTALL_WORKS = "1"
