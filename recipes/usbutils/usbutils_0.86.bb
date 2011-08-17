# -*- mode:python; -*-
DESCRIPTION = "Host side USB console utilities."
LICENSE = "GPLv2"

RECIPE_TYPES = "machine"

inherit autotools

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/linux-usb/usbutils-${PV}.tar.gz"

DEPENDS += "libusb-compat-dev libpthread"

sbindir = "${base_sbindir}"
bindir = "${base_bindir}"

EXTRA_OECONF = "--program-prefix="

do_patch[postfuncs] += "do_patch_rm_libusb"
do_patch_rm_libusb() {
	rm -rf ${S}/libusb
}

do_install[postfuncs] += "do_install_rm_usbids"
do_install_rm_usbids() {
	# The 0.86 Makefile.am installs both usb.ids and usb.ids.gz.
	if [ -f ${D}${datadir}/usb.ids.gz ]
	then
		rm -f ${D}${datadir}/usb.ids
	fi
}

PACKAGES =+ "${PN}-update"

FILES_${PN} += "${datadir}/usb*"
FILES_${PN}-update = "${sbindir}/update-usbids.sh"
