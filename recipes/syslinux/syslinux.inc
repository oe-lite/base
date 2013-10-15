DESCRIPTION = "A multi-purpose linux bootloader"
HOMEPAGE = "http://syslinux.zytor.com/"

COMPATIBLE_HOST_ARCHS = "i.86-.*-linux- x86_64-.*-linux-"

RECIPE_TYPES = "native machine"

inherit c make auto-package-utils

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/linux/utils/boot/syslinux/syslinux-${PV}.tar.bz2"

DEPENDS += "libuuid"

EXTRA_OEMAKE = " \
	BINDIR=${bindir} SBINDIR=${sbindir} LIBDIR=${libdir} \
	DATADIR=${datadir} MANDIR=${mandir} INCDIR=${includedir} \
"

do_configure() {
	# drop win32 targets or build fails
	sed -e 's,win32/\S*,,g' -i Makefile

	# clean installer executables included in source tarball
	oe_runmake clean
}

EXTRA_OEMAKE_COMPILE = 'CC="${CC} ${CFLAGS} ${LDFLAGS}"'

do_compile() {
	# Rebuild only the installer; keep precompiled bootloaders
	# as per author's request (doc/distrib.txt)
	oe_runmake ${EXTRA_OEMAKE_COMPILE} -C ${S}/com32/cmenu/
	oe_runmake ${EXTRA_OEMAKE_COMPILE} installer
}

do_install() {
	oe_runmake install INSTALLROOT="${D}"

	install -d ${D}${libdir}/syslinux/
	install -m 644 ${S}/core/ldlinux.sys ${D}${libdir}/syslinux/
	install -m 644 ${S}/core/ldlinux.bss ${D}${libdir}/syslinux/
}

AUTO_PACKAGE_UTILS = "extlinux gethostip isohybrid isohybrid.pl keytab-lilo \
	lss16toppm md5pass memdiskfind mkdiskimage ppmtolss16 \
	pxelinux-options sha1pass syslinux syslinux2ansi"

PACKAGES += "${PN}-mbr ${PN}-chain ${PN}-pxelinux ${PN}-isolinux ${PN}-misc"

FILES_${PN} = "${bindir}/syslinux"
FILES_${PN}-mbr = "${datadir}/${PN}/mbr.bin"
FILES_${PN}-chain = "${libdir}/${PN}/chain.c32"
FILES_${PN}-isolinux = "${libdir}/${PN}/isolinux.bin"
FILES_${PN}-pxelinux = "${libdir}/${PN}/pxelinux.0"
FILES_${PN}-dev += "${datadir}/${PN}/com32/lib*${SOLIBS} \
	${datadir}/${PN}/com32/include \
	${datadir}/${PN}/com32/com32.ld"
FILES_${PN}-staticdev += "${datadir}/${PN}/com32/lib*.a \
	${libdir}/${PN}/com32/lib*.a"
FILES_${PN}-misc = "${libdir}/${PN}/* ${bindir}/* ${datadir}"
