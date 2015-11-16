DESCRIPTION = "POCO C++ Libraries"
HOMEPAGE = "http://pocoproject.org"
LICENSE = "BSL-1.0"
DEPENDS += "libssl librt libpthread libc"
inherit cmake c c++

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "https://github.com/pocoproject/poco/archive/poco-${PV}-release.tar.gz"
S = "${SRCDIR}/poco-poco-${PV}-release"

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release -DPOCO_UNBUNDLED=On"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "PocoNetSSL PocoPDF PocoData PocoFoundation PocoJSON PocoUtil PocoMongoDB PocoNet PocoCrypto PocoXML PocoSevenZip PocoDataSQLite PocoZip"
AUTO_PACKAGE_LIBS_DEPENDS += "libm libpthread librt libstdc++ libc libdl ${PN}-dev"
AUTO_PACKAGE_LIBS_RDEPENDS += "libm libpthread librt libstdc++ libc libdl"

DEPENDS_${PN}-libpoconetssl += "libcrypto libpococrypto libpocofoundation libpocojson libpoconet libpocoutil libpocoxml libssl"
RDEPENDS_${PN}-libpoconetssl += "libcrypto libpococrypto libpocofoundation libpocojson libpoconet libpocoutil libpocoxml libssl"

DEPENDS_${PN}-libpocopdf += "libpocofoundation"
RDEPENDS_${PN}-libpocopdf += "libpocofoundation"

DEPENDS_${PN}-libpocodata += "libpocofoundation"
RDEPENDS_${PN}-libpocodata += "libpocofoundation"

DEPENDS_${PN}-libpocojson += "libpocofoundation"
RDEPENDS_${PN}-libpocojson += "libpocofoundation"

DEPENDS_${PN}-libpocoutil += "libpocofoundation libpocojson libpocoxml"
RDEPENDS_${PN}-libpocoutil += "libpocofoundation libpocojson libpocoxml"

DEPENDS_${PN}-libpocomongodb += "libpocofoundation libpoconet"
RDEPENDS_${PN}-libpocomongodb += "libpocofoundation libpoconet"

DEPENDS_${PN}-libpoconet += "libpocofoundation"
RDEPENDS_${PN}-libpoconet += "libpocofoundation"

DEPENDS_${PN}-libpococrypto += "libcrypto libpocofoundation libssl"
RDEPENDS_${PN}-libpococrypto += "libcrypto libpocofoundation libssl"

DEPENDS_${PN}-libpocoxml += "libpocofoundation"
RDEPENDS_${PN}-libpocoxml += "libpocofoundation"

DEPENDS_${PN}-libpocosevenzip += "libpocofoundation libpocojson libpocoutil libpocoxml"
RDEPENDS_${PN}-libpocosevenzip += "libpocofoundation libpocojson libpocoutil libpocoxml"

DEPENDS_${PN}-libpocodatasqlite += "libpocodata libpocofoundation"
RDEPENDS_${PN}-libpocodatasqlite += "libpocodata libpocofoundation"

DEPENDS_${PN}-libpocozip += "libpocofoundation libpocojson libpocoutil libpocoxml"
RDEPENDS_${PN}-libpocozip += "libpocofoundation libpocojson libpocoutil libpocoxml"

RDEPENDS_${PN} += "${LIBS_AUTO_RPACKAGES}"
