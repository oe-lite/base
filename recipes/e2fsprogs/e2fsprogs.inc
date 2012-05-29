# -*- mode:python; -*-
DESCRIPTION = "EXT2 Filesystem Utilities"
HOMEPAGE = "http://e2fsprogs.sf.net"

RECIPE_TYPES = "machine native sdk"

inherit autotools pkgconfig

DEPENDS = "native:gettext libpthread"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/e2fsprogs/e2fsprogs-${PV}.tar.gz"

EXTRA_OECONF = "--enable-elf-shlibs --enable-dynamic-e2fsck \
--disable-nls --disable-fsck"

# Use libblkid and libuuid from util-linux
DEPENDS += "libblkid libuuid"
EXTRA_OECONF += "--disable-libuuid --disable-libblkid"

do_compile[prefuncs] += "do_compile_pre"
do_compile_pre () {
	( cd util; ${BUILD_CC} subst.c -o subst )
}

EXTRA_OEMAKE = "V=1"

do_install[postfuncs] += "do_install_extra"
do_install_extra () {
    	oe_runmake install-libs DESTDIR=${D}

	rm ${D}${sbindir}/fsck.ext2
	rm ${D}${sbindir}/fsck.ext3
	rm ${D}${sbindir}/fsck.ext4*
	ln -sf ./e2fsck ${D}${sbindir}/fsck.ext2
	ln -sf ./e2fsck ${D}${sbindir}/fsck.ext3
	ln -sf ./e2fsck ${D}${sbindir}/fsck.ext4
	ln -sf ./e2fsck ${D}${sbindir}/fsck.ext4dev

	rm ${D}${sbindir}/mkfs.ext2
	rm ${D}${sbindir}/mkfs.ext3
	rm ${D}${sbindir}/mkfs.ext4*
	ln -sf ./mke2fs ${D}${sbindir}/mkfs.ext2
	ln -sf ./mke2fs ${D}${sbindir}/mkfs.ext3
	ln -sf ./mke2fs ${D}${sbindir}/mkfs.ext4
	ln -sf ./mke2fs ${D}${sbindir}/mkfs.ext4dev

	rm -f ${D}${sbindir}/findfs
	rm -f ${D}${sbindir}/e2label
	ln -sf ./tune2fs findfs
	ln -sf ./tune2fs e2label
}

RDEPENDS_${PN} = "libblkid libuuid e2fsprogs-badblocks"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "comerr:com_err e2p ext2fs ss"

FILES_${PN}-libcomerr-dev = "${includedir}/et ${datadir}/et"
PACKAGES =+ "${PN}-libcomerr-dev-utils ${PN}-libcomerr-dev-utils-doc \
	${PN}-libcomerr-dev-doc"
FILES_${PN}-libcomerr-dev-utils = "${bindir}/compile_et"
FILES_${PN}-libcomerr-dev-utils-doc = "${mandir}/man?/compile_et.*"
FILES_${PN}-libcomerr-dev-doc = "${mandir}/man?/com_err.*"
DEPENDS_${PN}-libcomerr-dev = "native:${PN}-libcomerr-dev-utils"
RDEPENDS_${PN}-libcomerr-dev = "host:${PN}-libcomerr-dev-utils"
RDEPENDS_${PN}-libcomerr += "libpthread"

FILES_${PN}-libe2p-dev = "${includedir}/e2p"

FILES_${PN}-libext2fs-dev = "${includedir}/ext2fs"
PACKAGES =+ "${PN}-libext2fs-dev-doc"
FILES_${PN}-libext2fs-dev-doc = "${infodir}/libext2fs*"

FILES_${PN}-libss-dev = "${includedir}/ss ${datadir}/ss"
PACKAGES =+ "${PN}-libss-dev-utils ${PN}-libss-dev-utils-doc"
FILES_${PN}-libss-dev-utils = "${bindir}/mk_cmds"
FILES_${PN}-libss-dev-utils-doc = "${mandir}/man?/mk_cmds.*"
DEPENDS_${PN}-libss-dev = "native:${PN}-libss-dev-utils"
RDEPENDS_${PN}-libss-dev = "host:${PN}-libss-dev-utils"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "e2fsck mke2fs tune2fs badblocks resize2fs e2freefrag \
	mklostfound:mklost+found uuidd e2initrdhelper logsave \
	debugfs dumpe2fs e2image e2undo filefrag chattr lsattr"

FILES_${PN}-e2fsck = "${sbindir}/fsck.ext*"
FILES_${PN}-e2fsck-doc = "${mandir}/man?/fsck.ext*.*"
PROVIDES_${PN}-e2fsck = "e2fsck fsck fsck-ext2 fsck-ext3 fsck-ext4 \
	${mandir}/man?/fsck.ext*.*"
RDEPENDS_${PN}-e2fsck = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid libuuid"

FILES_${PN}-mke2fs = "${sbindir}/mkfs.ext* ${sysconfdir}/mke2fs.conf"
FILES_${PN}-mke2fs-doc = "${mandir}/man?/mkfs.ext*.*"
PROVIDES_${PN}-mke2fs = "mke2fs mkfs-ext2 mkfs-ext3 mkfs-ext4 \
	${mandir}/man?/mkfs.ext*.*"
RDEPENDS_${PN}-mke2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid libuuid"

FILES_${PN}-tune2fs = "${sbindir}/e2label ${sbindir}/findfs \
	${mandir}/man?/e2label.* ${mandir}/man?/findfs.*"
RPROVIDES_${PN}-tune2fs = "tune2fs"
RDEPENDS_${PN}-tune2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid libuuid"

RDEPENDS_${PN}-resize2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p"

RDEPENDS_${PN}-e2freefrag = "${PN}-libext2fs ${PN}-libcomerr"

FILES_${PN}-e2initrdhelper = "${libdir}/e2initrd_helper"
RDEPENDS_${PN}-e2initrdhelper = "${PN}-libext2fs ${PN}-libcomerr \
    libblkid libuuid"

RDEPENDS_${PN}-e2initrdhelper = "${PN}-libcomerr ${PN}-libe2p"

PACKAGES =+ "${PN}-attr-utils"
RDEPENDS_${PN}-attr-utils = "${PN}-lsattr ${PN}-chattr"
ALLOW_EMPTY_${PN}-attr-utils = "1"
