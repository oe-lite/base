DESCRIPTION = "Util-linux-ng is a suite of essential utilities for any Linux system."
SECTION = "base"
LICENSE = "GPL"
BBCLASSEXTEND = "native"
DEPENDS = "pkgconfig"

inherit autotools_stage
AUTOTOOLS_STAGE_PKGCONFIG = "1"

DEFAULT_PREFERENCE = "-1"

INC_PR = "r1"

MA = "${@bb.data.getVar('PV', d, 1).split('.')[0]}"
MI = "${@bb.data.getVar('PV', d, 1).split('.')[1]}"

SRC_URI = "${KERNELORG_MIRROR}/pub/linux/utils/util-linux-ng/v${MA}.${MI}/util-linux-ng-${PV}.tar.bz2"


#FIXME: not working
PACKAGES =+ "${PN}-libuuid"
FILES_${PN}-libuuid = "${libdir}/libuuid*${SOLIBS}"

EXTRA_OECONF = "--without-ncurses --without-pam --disable-largefile \
--disable-mount --disable-fsck --disable-libblkid --disable-nls \
--disable-agetty --disable-cramfs --disable-switch_root \
--disable-rename --disable-schedutils --disable-wall \
--disable-makeinstall-chown --disable-use-tty-group --enable-libuuid \
--disable-tls \
"

do_configure_prepend() {
	cd ${S}
	./autogen.sh
}
