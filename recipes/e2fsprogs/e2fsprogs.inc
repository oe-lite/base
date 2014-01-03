# -*- mode:python; -*-
DESCRIPTION = "EXT2 Filesystem Utilities"
HOMEPAGE = "http://e2fsprogs.sf.net"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig

DEPENDS = "native:gettext ${DEPENDS_LIBC}"
DEPENDS_LIBC = "libpthread libc libgcc"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/e2fsprogs/e2fsprogs-${PV}.tar.gz"

EXTRA_OECONF = "--enable-elf-shlibs --enable-dynamic-e2fsck \
--disable-nls --disable-fsck"

# Use libblkid and libuuid from util-linux
DEPENDS += "libblkid libuuid"
EXTRA_OECONF += "--disable-libuuid --disable-libblkid"

DEPENDS += "libc libpthread"

do_compile[prefuncs] += "do_compile_pre"
do_compile_pre () {
	( cd util; ${BUILD_CC} subst.c -o subst )
}

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
AUTO_PACKAGE_LIBS = "com_err e2p ext2fs ss"

FILES_${PN}-libcom-err-dev = "${includedir}/et ${datadir}/et"
PACKAGES =+ "${PN}-libcom-err-dev-utils ${PN}-libcom-err-dev-utils-doc \
	${PN}-libcom-err-dev-doc"
FILES_${PN}-libcom-err-dev-utils = "${bindir}/compile_et"
FILES_${PN}-libcom-err-dev-utils-doc = "${mandir}/man?/compile_et.*"
FILES_${PN}-libcom-err-dev-doc = "${mandir}/man?/com_err.*"
DEPENDS_${PN}-libcom-err-dev = "native:${PN}-libcom-err-dev-utils"
RDEPENDS_${PN}-libcom-err-dev = "host:${PN}-libcom-err-dev-utils"
RDEPENDS_${PN}-libcom-err += "libpthread"

DEPENDS_${PN}-libe2p = "libc"
RDEPENDS_${PN}-libe2p = "libc"

FILES_${PN}-libe2p-dev = "${includedir}/e2p"

DEPENDS_${PN}-libext2fs = "libc libgcc libcom-err"
RDEPENDS_${PN}-libext2fs = "libc libgcc libcom-err"

FILES_${PN}-libext2fs-dev = "${includedir}/ext2fs"
PACKAGES =+ "${PN}-libext2fs-dev-doc"
FILES_${PN}-libext2fs-dev-doc = "${infodir}/libext2fs*"

DEPENDS_${PN}-libss = "libc libcom-err"
RDEPENDS_${PN}-libss = "libc libcom-err"

FILES_${PN}-libss-dev = "${includedir}/ss ${datadir}/ss"
PACKAGES =+ "${PN}-libss-dev-utils ${PN}-libss-dev-utils-doc"
FILES_${PN}-libss-dev-utils = "${bindir}/mk_cmds"
FILES_${PN}-libss-dev-utils-doc = "${mandir}/man?/mk_cmds.*"
DEPENDS_${PN}-libss-dev = "native:${PN}-libss-dev-utils"
RDEPENDS_${PN}-libss-dev = "host:${PN}-libss-dev-utils"

DEPENDS_${PN}-libcom-err =  "libc libpthread"
RDEPENDS_${PN}-libcom-err = "libc libpthread"

inherit auto-package-utils

FILES_${PN}-e2fsck = "${sbindir}/fsck.ext*"
FILES_${PN}-e2fsck-doc = "${mandir}/man?/fsck.ext*.*"
PROVIDES_${PN}-e2fsck = "e2fsck fsck fsck-ext2 fsck-ext3 fsck-ext4 \
	${mandir}/man?/fsck.ext*.*"
DEPENDS_${PN}-e2fsck = "libext2fs libcom-err libe2p \
	libblkid libuuid libgcc libc"
RDEPENDS_${PN}-e2fsck = "libext2fs libcom-err libe2p \
	libblkid libuuid libgcc libc"

FILES_${PN}-mke2fs = "${sbindir}/mkfs.ext* ${sysconfdir}/mke2fs.conf"
FILES_${PN}-mke2fs-doc = "${mandir}/man?/mkfs.ext*.*"
PROVIDES_${PN}-mke2fs = "mke2fs mkfs-ext2 mkfs-ext3 mkfs-ext4 \
	${mandir}/man?/mkfs.ext*.*"
DEPENDS_${PN}-mke2fs = "libext2fs libcom-err libe2p \
	libblkid libuuid libgcc libc"
RDEPENDS_${PN}-mke2fs = "libext2fs libcom-err libe2p \
	libblkid libuuid libgcc libc"

FILES_${PN}-tune2fs = "${sbindir}/e2label ${sbindir}/findfs \
	${mandir}/man?/e2label.* ${mandir}/man?/findfs.*"
DEPENDS_${PN}-tune2fs = "libext2fs libcom-err libe2p \
	libblkid libuuid libc"
RDEPENDS_${PN}-tune2fs = "libext2fs libcom-err libe2p \
	libblkid libuuid libc"

DEPENDS_${PN}-resize2fs = "libext2fs libcom-err libe2p libc libgcc"
RDEPENDS_${PN}-resize2fs = "libext2fs libcom-err libe2p libc libgcc"

DEPENDS_${PN}-e2freefrag = "libext2fs libcom-err libc"
RDEPENDS_${PN}-e2freefrag = "libext2fs libcom-err libc"

FILES_${PN}-e2initrdhelper = "${libdir}/e2initrd_helper"
RDEPENDS_${PN}-e2initrdhelper = "libext2fs libcom-err \
    libblkid libuuid"

RDEPENDS_${PN}-e2initrdhelper = "libcom-err libe2p"

RDEPENDS_${PN}-e4defrag = "libext2fs libcom-err"

DEPENDS_${PN}-logsave = "libc"
RDEPENDS_${PN}-logsave = "libc"

DEPENDS_${PN}-dumpe2fs = "libe2p libext2fs libcom-err \
    libuuid libc"
RDEPENDS_${PN}-dumpe2fs = "libe2p libext2fs libcom-err \
    libuuid libc"

DEPENDS_${PN}-debugfs = "libe2p libext2fs libcom-err libss \
    libblkid libuuid libgcc libc"
RDEPENDS_${PN}-debugfs = "libe2p libext2fs libcom-err libss \
    libblkid libuuid libgcc libc"

DEPENDS_${PN}-badblocks = "libe2p libext2fs libcom-err libss \
    libblkid libuuid libgcc libc"
RDEPENDS_${PN}-badblocks = "libe2p libext2fs libcom-err libss \
    libblkid libuuid libgcc libc"

DEPENDS_${PN}-mklostfound = "libc"
RDEPENDS_${PN}-mklostfound = "libc"

DEPENDS_${PN}-filefrag = "libc libgcc"
RDEPENDS_${PN}-filefrag = "libc libgcc"

DEPENDS_${PN}-uuidd = "libc libuuid"
RDEPENDS_${PN}-uuidd = "libc libuuid"

DEPENDS_${PN}-e2image = "libext2fs libcom-err libgcc libc"
RDEPENDS_${PN}-e2image = "libext2fs libcom-err libgcc libc"

DEPENDS_${PN}-e4defrag = "libext2fs libcom-err libgcc libc"
RDEPENDS_${PN}-e4defrag = "libext2fs libcom-err libgcc libc"

DEPENDS_${PN}-e2undo = "libext2fs libcom-err libc"
RDEPENDS_${PN}-e2undo = "libext2fs libcom-err libc"

DEPENDS_${PN}-chattr = "libe2p libcom-err libc"
RDEPENDS_${PN}-chattr = "libe2p libcom-err libc"

DEPENDS_${PN}-lsattr = "libe2p libcom-err libc"
RDEPENDS_${PN}-lsattr = "libe2p libcom-err libc"
