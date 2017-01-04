DESCRIPTION = "CppUnit is the C++ port of the famous JUnit framework for unit testing"
LICENSE = "GPL-2.0"

SRC_URI = "http://dev-www.libreoffice.org/src/cppunit-${PV}.tar.gz"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c++ autotools library auto-package-utils

LIBRARY="libcppunit"
LIBRARY_VERSION="0"

MA="${@d.get('PV').split('.')[0]}"
MI="${@d.get('PV').split('.')[1]}"

PROVIDES_${PN} += "${LIBRARY}-${MA}.${MI} ${LIBRARY}-${MA}.${MI}-0"

PROVIDES_${PN}[qa] += "allow-missing-soname:libcppunit"
PROVIDES_${PN}[qa] += "allow-missing-soname:libcppunit-0"

DEPENDS = "libdl libm libc libgcc-s libstdc++"
DEPENDS_${PN} = "libdl libm libc libgcc-s libstdc++"
RDEPENDS_${PN} = "libdl libm libc libgcc-s libstdc++"

AUTO_PACKAGE_UTILS = "cppunit-config DllPlugInTester"
AUTO_PACKAGE_UTILS_DEPENDS ="${PN}"
AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}"

EXTRA_OECONF += "--disable-doxygen --disable-dot"
