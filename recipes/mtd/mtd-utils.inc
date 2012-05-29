# -*- mode:python; -*-
DESCRIPTION = "Tools for managing memory technology devices."
HOMEPAGE = "http://www.linux-mtd.infradead.org/"

RECIPE_TYPES = "machine native sdk"

inherit c make auto-package-utils

SRC_URI = "git://git.infradead.org/mtd-utils.git;protocol=git;tag=v${PV}"
S = "${SRCDIR}/mtd-utils"

DEPENDS = "libz liblzo libuuid libm"

EXTRA_OEMAKE = "'LDFLAGS=${LDFLAGS}' \
	'CFLAGS=${CFLAGS} -I${S}/include -DWITHOUT_XATTR'"
EXTRA_OEMAKE:>native += " 'PREFIX=${prefix}' 'SBINDIR=${bindir}'"

do_install () {
	oe_runmake install DESTDIR=${D}
	install -d ${D}${includedir}/mtd/
	for f in ${S}/include/mtd/*.h; do
		install -m 0644 $f ${D}${includedir}/mtd/
	done
}

AUTO_PACKAGE_UTILS = "\
	bin2nand docfdisk doc_loadbios flashcp flash_erase flash_eraseall \
	flash_info flash_lock flash_otp_dump flash_otp_info flash_unlock \
	ftl_check ftl_format jffs2dump mkbootenv mkfs.jffs2 mkfs.ubifs mkpfi \
	mtd_debug mtdinfo nand2bin nanddump nandtest nandwrite nftldump \
	nftl_format pddcustomize pfi2bin pfiflash recv_image rfddump \
	rfdformat serve_image sumtool ubiattach ubicrc32 \
	ubidetach ubiformat ubigen ubimirror ubimkvol ubinfo ubinize \
	ubirename ubirmvol ubirsvol ubiupdatevol unubi \
"

FILES_mtd-utils-ubicrc32 = "${sbindir}/ubicrc32.pl"

RDEPENDS_${PN}-mkfs-jffs2 = "libz liblzo"
RDEPENDS_${PN}-mkfs-ubifs = "libz liblzo libuuid libm"

# The mtd-utils package is used to pull in all provided util features
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PROVIDES}"
