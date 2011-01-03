DESCRIPTION = "EXT2 Filesystem Utilities"
HOMEPAGE = "http://e2fsprogs.sf.net"
LICENSE = "GPL"
SECTION = "base"

BBCLASSEXTEND = "native sdk"

DEPENDS = "gettext-native \
	libblkid${RE} libuuid${RE} ${TOOLCHAIN_DEPENDS}"
TOOLCHAIN_DEPENDS = "${TARGET_ARCH}/sysroot-libpthread"
TOOLCHAIN_DEPENDS_recipe-native = ""

PACKAGES =+ "${PN}-e2fsck ${PN}-mke2fs ${PN}-tune2fs ${PN}-badblocks \
	${PN}-resize2fs ${PN}-e2freefrag ${PN}-uuidd \
	${PN}-libext2fs ${PN}-libe2p ${PN}-libcomerr ${PN}-libss"

RPROVIDES_${PN}-mke2fs = "mke2fs${RE} \
	mkfs-ext2${RE} mkfs-ext3${RE} mkfs-ext4${RE}"
RPROVIDES_${PN}-e2fsck = "fsck${RE} \
	fsck-ext2${RE} fsck-ext3${RE} fsck-ext4${RE}"
RPROVIDES_${PN}-tune2fs = "tune2fs${RE}"

RDEPENDS_${PN}-libext2fs	= "${PN}-libcomerr"
DEPENDS_${PN}-libext2fs		= "${PN}-libcomerr"
RDEPENDS_${PN}-libe2p		= ""
RDEPENDS_${PN}-libcomerr	= "${HOST_ARCH}/sysroot-libpthread"
DEPENDS_${PN}-libcomerr		= "${HOST_ARCH}/sysroot-libpthread"
RDEPENDS_${PN}-libss		= ""

RDEPENDS_${PN} = "libblkid${RE} libuuid${RE} e2fsprogs${RE}-badblocks"
RDEPENDS_${PN}-e2fsck = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid${RE} libuuid${RE}"
RDEPENDS_${PN}-mke2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid${RE} libuuid${RE}"
RDEPENDS_${PN}-tune2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p \
	libblkid${RE} libuuid${RE}"
RDEPENDS_${PN}-resize2fs = "${PN}-libext2fs ${PN}-libcomerr ${PN}-libe2p"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/e2fsprogs/e2fsprogs-${PV}.tar.gz"

inherit autotools pkgconfig

EXTRA_OECONF = "--enable-elf-shlibs --enable-dynamic-e2fsck \
--disable-nls --disable-libuuid --disable-libblkid --disable-fsck"

# FIXME: find out if this is still needed
PARALLEL_MAKE = ""

do_compile_prepend () {
	find ./ -print|xargs chmod u=rwX
	( cd util; ${BUILD_CC} subst.c -o subst )
}

do_install_append () {
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

FILES_${PN} += "${libdir}/e2initrd_helper"
FILES_${PN}-e2fsck = "${sbindir}/e2fsck ${sbindir}/fsck.ext*"
FILES_${PN}-mke2fs = "${sbindir}/mke2fs ${sbindir}/mkfs.ext*"
FILES_${PN}-tune2fs = "${sbindir}/tune2fs ${sbindir}/e2label ${sbindir}/findfs"
FILES_${PN}-badblocks = "${sbindir}/badblocks"
FILES_${PN}-resize2fs = "${sbindir}/resize2fs"
FILES_${PN}-e2freefrag = "${sbindir}/e2freefrag"
FILES_${PN}-uuidd = "${sbindir}/uuidd"
FILES_${PN}-libcomerr = "${libdir}/libcom_err${SOLIBS}"
FILES_${PN}-libss = "${libdir}/libss${SOLIBS}"
FILES_${PN}-libext2fs = "${libdir}/libext2fs${SOLIBS}"
FILES_${PN}-libe2p = "${libdir}/libe2p${SOLIBS}"
