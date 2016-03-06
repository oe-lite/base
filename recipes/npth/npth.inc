SUMMARY = "New GNU Portable Threads library"
HOMEPAGE = "http://www.gnupg.org/software/pth/"
SECTION = "libs"
LICENSE = "LGPLv3+ & GPLv2+"
SRC_URI = "ftp://ftp.gnupg.org/gcrypt/${PN}/${P}.tar.bz2 \
           file://pkgconfig.patch \
          "

DEPENDS = "libc libpthread"
RECIPE_TYPES = "native machine sdk"
inherit autotools pkgconfig library auto-package-utils binconfig

AUTO_PACKAGE_UTILS += "npth-config"

FILES_${PN} = "${libdir}/libnpth.so.*"
DEPENDS_${PN} += "libc libpthread"
RDEPENDS_${PN} += "libc libpthread"
LIBRARY_VERSION = "0"
