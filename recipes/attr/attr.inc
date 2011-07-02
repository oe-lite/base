DESCRIPTION = "Commands for Manipulating Filesystem Extended Attributes"
LICENSE = "GPLv2+"

RECIPE_TYPES = "machine native"

SRC_URI = "http://mirror.its.uidaho.edu/pub/savannah/attr/attr-${PV}.src.tar.gz"

inherit autotools

AUTOTOOLS_DISTCLEAN = "0"

do_install() {
	export PKG_BIN_DIR=${D}${bindir}
	export PKG_SBIN_DIR=${D}${sbindir}
	export PKG_LIB_DIR=${D}${libdir}
	export PKG_DEVLIB_DIR=${D}${libexecdir}
	export PKG_INC_DIR=${D}${includedir}/attr
	export PKG_MAN_DIR=${D}${mandir}
	export PKG_DOC_DIR=${D}${datadir}/doc/attr
	export PKG_LOCALE_DIR=${D}${datadir}/locale
        # ensure the subdir Makefile do not use the (wrong) variable overrides from the include file
        export MAKE="${MAKE} -e"

	oe_runmake -e install install-dev install-lib

	# Move .a and .la into libdir and remove symlinks pointing to ${S}
	for file in ${D}${libexecdir}/*.a ${D}${libexecdir}/*.la ; do
		rm ${D}${libdir}/$(basename $file)
		mv $file ${D}${libdir}
	done
	rm -rf ${D}${libexecdir}
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "attr"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"

RDEPENDS_${PN} += "${PN}-libattr"

FILES_${PN}-dev += "${libexecdir}"
