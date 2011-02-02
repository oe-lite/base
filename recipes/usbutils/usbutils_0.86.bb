DESCRIPTION = "Host side USB console utilities."
SECTION = "base"
LICENSE = "GPLv2"
PRIORITY = "optional"

inherit autotools

DEPENDS += "libusb-compat-dev ${TARGET_ARCH}/sysroot-libpthread"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/linux-usb/usbutils-${PV}.tar.gz"


EXTRA_OECONF = "--program-prefix="
sbindir = "${base_sbindir}"
bindir = "${base_bindir}"
do_configure_prepend() {
	rm -rf ${S}/libusb
}

do_install_append() {
	# The 0.86 Makefile.am installs both usb.ids and usb.ids.gz.
	if [ -f ${D}${datadir}/usb.ids.gz ]
	then
		rm -f ${D}${datadir}/usb.ids
	fi
}

PACKAGES =+ "${PN}-update"

FILES_${PN} += "${datadir}/usb*"
FILES_${PN}-update = "${sbindir}/update-usbids.sh"
