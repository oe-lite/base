DESCRIPTION = "GNOME XML Parser library"
LICENSE = "MIT"

inherit autotools pkgconfig binconfig

BBCLASSEXTEND = "native"

DEPENDS = "${TARGET_ARCH}/sysroot-libdl \
           ${TARGET_ARCH}/sysroot-libm"
DEPENDS_recipe-native =""

SRC_URI = "ftp://xmlsoft.org/${BPN}/${BPN}-${PV}.tar.gz"

EXTRA_OECONF = "\
 --without-legacy \
 --with-catalog \
 --with-docbook \
 --with-c14n"

EXTRA_OECONF += "--without-python"
EXTRA_OECONF_native += " --with-python"

export LDFLAGS += "-ldl"

PACKAGES =+ "${PN}-utils"
FILES_${PN} = "${libexecdir}/* ${libdir}/lib*${SOLIBS} \
            ${sysconfdir} ${sharedstatedir} ${localstatedir} \
            ${base_libdir}/*${SOLIBS} \
            ${datadir}/${PN} ${libdir}/${PN}/* \
            ${datadir}/pixmaps ${datadir}/applications \
            ${datadir}/idl ${datadir}/omf ${datadir}/sounds \
            ${libdir}/bonobo/servers"

FILES_${PN}-utils = "${bindir}/xmllint ${bindir}/xmlcatalog ${libdir}/*.sh"
FILES_${PN}-doc += "${datadir}/gtk-doc"
