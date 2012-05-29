# -*- mode:python; -*-
DESCRIPTION = "Util-linux is a suite of essential utilities for any \
	Linux system."

RECIPE_TYPES = "machine native sdk"

inherit autotools autotools-autoreconf

require conf/fetch/kernelorg.conf
MA = "${@bb.data.getVar('PV', d, 1).split('.')[0]}"
MI = "${@bb.data.getVar('PV', d, 1).split('-')[0].split('.')[1]}"
SRC_URI = "${KERNELORG_MIRROR}/linux/utils/${PN}/v${MA}.${MI}/${P}.tar.bz2"

DEPENDS = "libc libutil libcrypt libz libtermcap"

EXTRA_OECONF = "\
--disable-rpath \
--disable-makeinstall-chown --disable-use-tty-group \
"

RECIPE_FLAGS += "ncurses"
EXTRA_OECONF += "${EXTRA_OECONF_NCURSES}"
EXTRA_OECONF_NCURSES = " --without-ncurses"
EXTRA_OECONF_NCURSES:USE_ncurses = " --with-ncurses"
DEPENDS:>USE_ncurses = " libncurses"
# FIXME: add ncursesw USE flag support

RECIPE_FLAGS += "pam"
EXTRA_OECONF += "${EXTRA_OECONF_PAM}"
EXTRA_OECONF_PAM = " --without-pam"
EXTRA_OECONF_PAM:USE_pam = " --with-pam"
# FIXME: test and debug pam support (at least som DEPENDS must be needed...)

RECIPE_FLAGS += "nls"
EXTRA_OECONF += "${EXTRA_OECONF_NLS}"
EXTRA_OECONF_NLS = " --disable-nls"
EXTRA_OECONF_NLS:USE_nls = " --enable-nls"

RECIPE_FLAGS += "largefile"
EXTRA_OECONF += "${EXTRA_OECONF_LARGEFILE}"
EXTRA_OECONF_LARGEFILE = " --disable-largefile"
EXTRA_OECONF_LARGEFILE:USE_largefile = " --enable-largefile"

EXTRA_OEMAKE += "V=1"

# Grrrr... at least some versions of util-linux insists on having
# an sbin dir even though it is told to put everything in bin.  At
# least it seems to respect requests on dropping usr prefix
do_install[postfuncs] += "do_install_sbin_fixup"
do_install_sbin_fixup () {
        if [ ${base_sbindir} != "/sbin" ] ; then
		if [ -d ${D}/sbin ] ; then
			cp -ar ${D}/sbin/. ${D}${bindir}/. \
				&& rm -rf ${D}/sbin
		fi
	fi
}

FILES_${PN}-doc += "${datadir}/getopt/"

inherit auto-package-utils auto-package-libs

AUTO_PACKAGE_UTILS = "agetty blkid cal chkdupexe chrt col colcrt colrm \
	column cytune ddate dmesg fallocate fdisk findfs findmnt flock fsck \
	fsck.cramfs fsck.minix getopt hexdump hwclock ionice ipcmk ipcrm ipcs \
	isosize line logger look losetup lsblk lscpu mkfs mkfs.bfs mkfs.cramfs \
	mkfs.minix mcookie mkswap mount namei pivot_root rename renice \
	rev script scriptreplay setarch setsid sfdisk swaplabel swapon \
	switch_root tailf taskset umount unshare uuidd uuidgen wall whereis \
	wipefs addpart blockdev ctrlaltdel delpart fdformat fsfreeze fstrim \
	ldattach readprofile rtcwake tunelp"
AUTO_PACKAGE_UTILS:>USE_ncurses = " more cfdisk"
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PACKAGES}"

AUTO_PACKAGE_LIBS = "blkid uuid mount"
FILES_${PN}-libblkid-dev += "${includedir}/blkid"
FILES_${PN}-libuuid-dev += "${includedir}/uuid"
FILES_${PN}-libmount-dev += "${includedir}/libmount"

FILES_${PN}-setarch = "${bindir}/linux32 ${bindir}/linux64 ${bindir}/ppc \
	${bindir}/ppc32 ${bindir}/ppc64"
FILES_${PN}-swapon = "${sbindir}/swapoff"
