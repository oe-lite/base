DESCRIPTION = "GNOME XML Parser library"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath pkgconfig library binconfig

SRC_URI = "ftp://xmlsoft.org/${PN}/${PN}-${PV}.tar.gz"

DEPENDS = "libc libm ${DEPENDS_HOST_OS} ${DEPENDS_PYTHON}"
DEPENDS_PYTHON = ""
DEPENDS_PYTHON:native = "python-runtime"
DEPENDS_HOST_OS = "libdl"
DEPENDS_HOST_OS:HOST_LIBC_mingw = ""
DEPENDS_${PN} += "libc libm ${DEPENDS_HOST_OS}"

EXTRA_OECONF_PYTHON = "--with-python-install-dir=${libdir}/python"
EXTRA_OECONF_PYTHON:machine = "--without-python"
EXTRA_OECONF_PYTHON:sdk = "--without-python"

EXTRA_OECONF = "\
 --without-legacy \
 --with-c14n \
 ${EXTRA_OECONF_PYTHON}"

LDFLAGS_LDL = "-ldl"
LDFLAGS_LDL:TARGET_OS_mingw32 = ""
export LDFLAGS += "${LDFLAGS_LDL}"

PACKAGES += "${PN}-utils ${PN}-python ${PN}-python-dev ${PN}-python-dbg"
FILES_${PN} = "${libexecdir}/* ${sharedlibdir}/lib*${SOLIBS} \
            ${sysconfdir} ${sharedstatedir} ${localstatedir} \
            ${base_libdir}/*${SOLIBS} \
            ${datadir}/${PN} ${libdir}/${PN}/* \
            ${datadir}/pixmaps ${datadir}/applications \
            ${datadir}/idl ${datadir}/omf ${datadir}/sounds \
            ${libdir}/bonobo/servers"

FILES_${PN}-utils = "${bindir}/xmllint* ${bindir}/xmlcatalog* ${libdir}/*.sh"
FILES_${PN}-doc += "${datadir}/gtk-doc"
DEPENDS_${PN}-utils += "libc libm ${DEPENDS_HOST_OS} libxml2"
RDEPENDS_${PN}-utils += "libc libm ${DEPENDS_HOST_OS} libxml2"

FILES_${PN}-python += "${libdir}/python/libxml2mod.so \
			   ${libdir}/python/libxml2.py \
			   ${libdir}/python/drv_libxml2.py"
FILES_${PN}-python-dev += "${libdir}/python/libxml2mod.la \
			       ${libdir}/python/libxml2mod.a"
FILES_${PN}-python-dbg += "${libdir}/python/.debug/libxml2mod.so"
