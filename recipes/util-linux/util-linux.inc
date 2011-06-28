DESCRIPTION = "Util-linux is a suite of essential utilities for any Linux system."
LICENSE = "GPL"

BBCLASSEXTEND = "native sdk"

DEFAULT_PREFERENCE = "-1"

PACKAGES =+ "\
${PN}-mount ${PN}-mount-doc \
${PN}-fsck ${PN}-fsck-doc \
${PN}-mkfs ${PN}-mkfs-doc \
${PN}-minix ${PN}-minix-doc \
${PN}-cramfs ${PN}-cramfs-doc \
${PN}-bfs ${PN}-bfs-doc \
${PN}-fdisk ${PN}-fdisk-doc \
${PN}-sfdisk ${PN}-sfdisk-doc \
${PN}-pivot-root ${PN}-pivot-root-doc \
${PN}-switch-root ${PN}-switch-root-doc \
${PN}-agetty ${PN}-agetty-doc \
${PN}-blkid ${PN}-blkid-doc \
${PN}-libblkid ${PN}-libblkid-dev \
${PN}-uuidd ${PN}-uuidd-doc \
${PN}-uuidgen ${PN}-uuidgen-doc \
${PN}-libuuid ${PN}-libuuid-dev \
${PN}-wall ${PN}-wall-doc \
${PN}-fallocate ${PN}-fallocate-doc \
${PN}-getopt ${PN}-getopt-doc \
${PN}-taskset ${PN}-taskset-doc \
${PN}-whereis ${PN}-whereis-doc \
"

RPROVIDES_${PN}-mount		= "mount${RE}"
RPROVIDES_${PN}-fsck		= "fsck${RE}"
RPROVIDES_${PN}-mkfs		= "mkfs${RE}"
RPROVIDES_${PN}-minix		= "mkfs-minix${RE} fsck-minix${RE}"
RPROVIDES_${PN}-cramfs		= "mkfs-cramfs${RE} fsck-cramfs${RE}"
RPROVIDES_${PN}-bfs		= "mkfs-bfs${RE} fsck-bfs${RE}"
RPROVIDES_${PN}-fdisk		= "fdisk${RE}"
RPROVIDES_${PN}-sfdisk		= "sfdisk${RE}"
RPROVIDES_${PN}-pivot-root	= "pivot-root${RE}"
RPROVIDES_${PN}-switch-root	= "switch-root${RE}"
RPROVIDES_${PN}-blkid		= "blkid${RE}"
RPROVIDES_${PN}-agetty		= "agetty${RE}"
RPROVIDES_${PN}-uuidd		= "uuidd${RE}"
RPROVIDES_${PN}-uuidgen		= "uuidgen${RE}"
RPROVIDES_${PN}-wall		= "wall${RE}"
RPROVIDES_${PN}-fallocate	= "fallocate${RE}"
RPROVIDES_${PN}-getopt		= "getopt${RE}"
RPROVIDES_${PN}-taskset		= "taskset${RE}"
RPROVIDES_${PN}-whereis		= "whereis${RE}"

RPROVIDES_${PN}-libblkid	= "libblkid${RE}"
PROVIDES_${PN}-libblkid-dev	= "libblkid${RE}"
DEPENDS_${PN}-libblkid-dev	= "${PN}-libblkid"

RPROVIDES_${PN}-libuuid		= "libuuid${RE}"
PROVIDES_${PN}-libuuid-dev	= "libuuid${RE}"
DEPENDS_${PN}-libuuid-dev	= "${PN}-libuuid"

SYSROOT_DEPENDS = "\
    ${TARGET_ARCH}/sysroot-libc \
    ${TARGET_ARCH}/sysroot-libutil \
    ${TARGET_ARCH}/sysroot-libcrypt \
"
SYSROOT_DEPENDS_recipe-native = ""
DEPENDS = "zlib${RE} libtermcap${RE} ${SYSROOT_DEPENDS}"

require conf/fetch/kernelorg.conf
MA = "${@bb.data.getVar('PV', d, 1).split('.')[0]}"
MI = "${@bb.data.getVar('PV', d, 1).split('-')[0].split('.')[1]}"
SRC_URI = "${KERNELORG_MIRROR}/pub/linux/utils/${BPN}/v${MA}.${MI}/${BP}.tar.bz2"

inherit autotools autotools-autoreconf

EXTRA_OEMAKE += "V=1"

# FIXME: add DISTRO_FEATURE flags for enable/disable of ncurses, pam and nls.

EXTRA_OECONF = "\
--disable-rpath \
--disable-largefile \
--disable-makeinstall-chown --disable-use-tty-group \
--without-pam \
--disable-nls \
"

RECIPE_OPTIONS += "ncurses"
NCURSES_EXTRA_OECONF = "--without-ncurses"
NCURSES_EXTRA_OECONF_RECIPE_OPTION_ncurses = ""
EXTRA_OECONF += "${NCURSES_EXTRA_OECONF}"
NCURSES_DEPENDS = ""
NCURSES_DEPENDS_RECIPE_OPTION_ncurses = "libncurses${RE}"
DEPENDS += "${NCURSES_DEPENDS}"

# Grrrr... at least some versions of util-linux insists on having
# an sbin dir even though it is told to put everything in bin.  At
# least it seems to respect requests on dropping usr prefix
do_install_append_recipe-native () {
	(
	cd ${D}
	if [ -d sbin ] ; then
		if [ -d bin ] ; then
			mv sbin/* bin/
		else
			mv sbin bin
		fi
	fi
	)
}

FILES_${PN}-mount = "${bindir}/mount ${bindir}/umount"
FILES_${PN}-mount-doc = "${mandir}/man8/mount.8 ${mandir}/man8/umount.8"
FILES_${PN}-fsck = "${sbindir}/fsck"
FILES_${PN}-fsck-doc = "${mandir}/man8/fsck.8"
FILES_${PN}-mkfs = "${sbindir}/mkfs"
FILES_${PN}-mkfs-doc = "${mandir}/man8/mkfs.8"
FILES_${PN}-minix = "${sbindir}/*.minix"
FILES_${PN}-minix-doc = "${mandir}/man8/*.minix.8"
FILES_${PN}-bfs = "${sbindir}/*.bfs"
FILES_${PN}-bfs-doc = "${mandir}/man8/*.bfs.8"
FILES_${PN}-fdisk = "${sbindir}/fdisk"
FILES_${PN}-fdisk-doc = "${mandir}/man8/fdisk.8"
FILES_${PN}-sfdisk = "${sbindir}/sfdisk"
FILES_${PN}-sfdisk-doc = "${mandir}/man8/sfdisk.8"
FILES_${PN}-pivot-root = "${sbindir}/pivot_root"
FILES_${PN}-pivot-root-doc = "${mandir}/man8/pivot_root.8"
FILES_${PN}-switch-root = "${sbindir}/switch_root"
FILES_${PN}-switch-root-doc = "${mandir}/man8/switch_root.8"
FILES_${PN}-agetty = "${sbindir}/agetty"
FILES_${PN}-agetty-doc = "${mandir}/man8/agetty.8"
FILES_${PN}-cramfs = "${sbindir}/*.cramfs"
FILES_${PN}-cramfs-doc = "${mandir}/man8/*.cramfs.8"
FILES_${PN}-blkid = "${sbindir}/blkid"
FILES_${PN}-blkid-doc = "${mandir}/man8/blkid.8"
FILES_${PN}-libblkid = "${libdir}/libblkid*${SOLIBS}"
FILES_${PN}-libblkid-dev = "${includedir}/blkid ${libdir}/libblkid${SOLIBSDEV} ${libdir}/libblkid.a ${libdir}/libblkid.la ${libdir}/pkgconfig/blkid.pc"
FILES_${PN}-uuidd = "${sbindir}/uuidd"
FILES_${PN}-uuidd-doc = "${mandir}/man8/uuidd.8"
FILES_${PN}-uuidgen = "${bindir}/uuidgen"
FILES_${PN}-uuidgen-doc = "${mandir}/man1/uuidgen.1"
FILES_${PN}-libuuid = "${libdir}/libuuid*${SOLIBS}"
FILES_${PN}-libuuid-dev = "${includedir}/uuid ${libdir}/libuuid${SOLIBSDEV} ${libdir}/libuuid.a ${libdir}/libuuid.la ${libdir}/pkgconfig/uuid.pc"
FILES_${PN}-wall = "${bindir}/wall"
FILES_${PN}-wall-doc = "${mandir}/man1/wall.1"
FILES_${PN}-fallocate = "${bindir}/fallocate"
FILES_${PN}-fallocate-doc = "${mandir}/man1/fallocate.1"
FILES_${PN}-getopt = "${bindir}/getopt ${datadir}/getopt"
FILES_${PN}-getopt-doc = "${mandir}/man1/getopt.1"
FILES_${PN}-taskset = "${bindir}/taskset"
FILES_${PN}-taskset-doc = "${mandir}/man1/taskset.1"
FILES_${PN}-whereis = "${bindir}/whereis"
FILES_${PN}-whereis-doc = "${mandir}/man1/whereis.1"
