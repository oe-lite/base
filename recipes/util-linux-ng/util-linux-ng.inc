DESCRIPTION = "Util-linux-ng is a suite of essential utilities for any Linux system."
SECTION = "base"
LICENSE = "GPL"
DEPENDS = "pkgconfig"

BBCLASSEXTEND = "native"


DEFAULT_PREFERENCE = "-1"

INC_PR = "r2"

MA = "${@bb.data.getVar('PV', d, 1).split('.')[0]}"
MI = "${@bb.data.getVar('PV', d, 1).split('.')[1]}"

SRC_URI = "${KERNELORG_MIRROR}/pub/linux/utils/util-linux-ng/v${MA}.${MI}/util-linux-ng-${PV}.tar.bz2"

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

RPROVIDES_${PN}-libblkid = "libblkid${RE}"
PROVIDES_${PN}-libblkid-dev = "libblkid${RE}-dev"
DEPENDS_${PN}-libblkid-dev =  "${PN}-libblkid"
inherit autotools

RPROVIDES_${PN}-libuuid = "libuuid${RE}"
PROVIDES_${PN}-libuuid-dev = "libuuid${RE}-dev"
DEPENDS_${PN}-libuuid-dev =  "${PN}-libuuid"

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

# FIXME: add DISTRO_FEATURE flags for enable/disable of ncurses, pam and nls.

EXTRA_OECONF = "\
--disable-rpath \
--disable-largefile \
--disable-makeinstall-chown --disable-use-tty-group \
--without-ncurses \
--without-pam \
--disable-nls \
"

do_configure_prepend () {
	cd ${S}
	./autogen.sh
}

# Grrrr... at least some versions of util-linux-ng insists on having
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
