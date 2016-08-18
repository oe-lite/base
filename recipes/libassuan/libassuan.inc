SUMMARY = "IPC library used by GnuPG and GPGME"
HOMEPAGE = "http://www.gnupg.org/related_software/libassuan/"
BUGTRACKER = "https://bugs.g10code.com/gnupg/index"
LICENSE = "GPLv3 & LGPLv2.1+"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "native machine sdk"

inherit autotools pkgconfig library auto-package-utils binconfig

DEPENDS = "libgpg-error libgpg-error-config"

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/libassuan/libassuan-${PV}.tar.bz2"

AUTO_PACKAGE_UTILS += "libassuan-config"
DEPENDS_${PN} += "libc libgpg-error"
RDEPENDS_${PN} += "libc libgpg-error"
