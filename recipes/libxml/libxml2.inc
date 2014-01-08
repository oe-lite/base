DESCRIPTION = "GNOME XML Parser library"

RECIPE_TYPES = "machine native sdk"

inherit autotools make-vpath pkgconfig library binconfig

SRC_URI = "ftp://xmlsoft.org/${PN}/${PN}-${PV}.tar.gz"

DEPENDS = "libc libm ${DEPENDS_HOST_OS}"
DEPENDS_HOST_OS = "libdl"
DEPENDS_HOST_OS:HOST_LIBC_mingw = ""
DEPENDS_${PN} += "libc libm ${DEPENDS_HOST_OS}"

EXTRA_OECONF = "\
 --without-legacy \
 --with-catalog \
 --with-docbook \
 --without-python \
 --with-c14n"

LDFLAGS_LDL = "-ldl"
LDFLAGS_LDL:TARGET_OS_mingw32 = ""
export LDFLAGS += "${LDFLAGS_LDL}"

PACKAGES =+ "${PN}-utils"
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
