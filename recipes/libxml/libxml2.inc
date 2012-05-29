DESCRIPTION = "GNOME XML Parser library"

RECIPE_TYPES = "machine native sdk"

inherit autotools pkgconfig library binconfig

SRC_URI = "ftp://xmlsoft.org/${PN}/${PN}-${PV}.tar.gz"

DEPENDS = "libdl libm"

EXTRA_OECONF = "\
 --without-legacy \
 --with-catalog \
 --with-docbook \
 --with-c14n"

EXTRA_OECONF += "${EXTRA_OECONF_PYTHON}"
EXTRA_OECONF_PYTHON = "--without-python"
EXTRA_OECONF_PYTHON:native = "--with-python"

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
