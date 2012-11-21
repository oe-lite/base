DESCRIPTION = "Tools for the Linux Standard Wireless Extension Subsystem"
HOMEPAGE = "http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/Tools.html"
LICENSE = "GPLv2 & (LGPLv2.1 | MPL-1.1 | BSD)"

inherit make c

DEPENDS += "libm"

SRC_URI = "http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/wireless_tools.29.tar.gz"
S = "${SRCDIR}/wireless_tools.29"

CFLAGS =+ "-I${S}"
EXTRA_OEMAKE = "-e 'BUILD_SHARED=y' \
		'INSTALL_DIR=${D}${base_sbindir}' \
		'INSTALL_LIB=${D}${libdir}' \
		'INSTALL_INC=${D}${includedir}' \
		'INSTALL_MAN=${D}${mandir}'"

do_compile() {
	oe_runmake all libiw.a
}

do_install() {
	oe_runmake PREFIX=${D} install-iwmulticall install-dynamic install-man install-hdr
	install -d ${D}${sbindir}
	install -m 0755 ifrename ${D}${sbindir}/ifrename
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "iw"
FILES_${PN}-libiw-dev = "${includedir}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "iwconfig ifrename"
FILES_${PN}-iwconfig = "${base_sbindir}/iwgetid ${base_sbindir}/iwlist \
	${base_sbindir}/iwpriv ${base_sbindir}/iwspy"
RDEPENDS_${PN}-ifrename += "libiw"
