DESCRIPTION = "The XSLT C library for GNOME"

RECIPE_TYPES = "native"

inherit auto-package-libs auto-package-utils autotools pkgconfig

SRC_URI = "ftp://xmlsoft.org/${PN}/${PN}-${PV}.tar.gz"

DEPENDS = "libc libm libxml2"

AUTO_PACKAGE_UTILS = "xsltproc xslt-config"
# FIXME:
# auto-package-libs does not work well when a recipe is name libfoo
# since the default recipe provides will collide with the auto-package ones
# MultipleProviders: multiple providers for native:libxslt_1.1.28:
#                     native:libxslt-libxslt native:libxslt
AUTO_PACKAGE_LIBS = "exslt"
LIBRARY_VERSION-libexslt = "2"
AUTO_PACKAGE_UTILS_DEPENDS += "libexslt libxml2 libxslt"
AUTO_PACKAGE_LIBS_DEPENDS += "libxml2"

FILES_${PN}-dev += "${libdir}/xsltConf.sh"

DEPENDS_${PN} += "libxml2"
DEPENDS_${PN}-libexslt += "libxslt"
PROVIDES_${PN}-libexslt[qa] += "allow-missing-provides:libexslt-0"
PROVIDES_${PN}[qa] += "allow-missing-provides:libxslt allow-missing-provides:libxslt-1"

PACKAGES += "${PN}-python ${PN}-python-dev ${PN}-python-dbg"

FILES_${PN}-python += "${libdir}/python*/site-packages/libxsltmod.so \
                       ${libdir}/python*/site-packages/libxslt.py"
FILES_${PN}-python-dev += "${libdir}/python*/site-packages/libxsltmod.la \
                           ${libdir}/python*/site-packages/libxsltmod.a"
FILES_${PN}-python-dbg += "${libdir}/python*/site-packages/.debug/libxsltmod.so"
