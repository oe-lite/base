DESCRIPTION = "Util-linux-ng is a suite of essential utilities for any Linux system."
SECTION = "base"
LICENSE = "GPL"
DEPENDS = "pkgconfig"

BBCLASSEXTEND = "native"

inherit autotools_stage
AUTOTOOLS_STAGE_PKGCONFIG = "1"

DEFAULT_PREFERENCE = "-1"

INC_PR = "r2"

MA = "${@bb.data.getVar('PV', d, 1).split('.')[0]}"
MI = "${@bb.data.getVar('PV', d, 1).split('.')[1]}"

SRC_URI = "${KERNELORG_MIRROR}/pub/linux/utils/util-linux-ng/v${MA}.${MI}/util-linux-ng-${PV}.tar.bz2"

PACKAGES =+ "${PN}-libuuid"
FILES_${PN}-libuuid = "${libdir}/libuuid*${SOLIBS}"

FILES_${PN}-dev += "${datadir}/getopt"

EXTRA_OECONF = "--without-ncurses --without-pam --disable-largefile \
--disable-mount --disable-fsck --disable-libblkid --disable-nls \
--disable-agetty --disable-cramfs --disable-switch_root \
--disable-rename --disable-schedutils --disable-wall \
--disable-makeinstall-chown --disable-use-tty-group --enable-libuuid \
--disable-tls \
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
