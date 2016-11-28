DESCRIPTION = "A general purpose cryptographic library based on the code from GnuPG"
HOMEPAGE = "http://directory.fsf.org/project/libgcrypt/"
BUGTRACKER = "https://bugs.g10code.com/gnupg/index"

# helper program gcryptrnd and getrandom are under GPL, rest LGPL
LICENSE = "GPL-2.0+ & LGPL-2.1+"
RECIPE_TYPES = "native machine sdk"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools binconfig pkgconfig library

DEPENDS = "libgpg-error libgpg-error-config libcap libpthread"
DEPENDS_${PN} += "libgpg-error libc libcap libpthread"
RDEPENDS_${PN} += "libgpg-error libc libcap libpthread"

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/libgcrypt/libgcrypt-${PV}.tar.gz"

RECIPE_FLAGS = "libgcrypt_capabilities"
DEFAULT_USE_libgcrypt_capabilities = True

EXTRA_OECONF = "--without-pth --disable-asm --with-gpg-error-prefix=${MACHINE_SYSROOT}/usr ${EXTRA_OECONF_CAPABILITIES}"
EXTRA_OECONF_CAPABILITIES = "--without-capabilities"
EXTRA_OECONF_CAPABILITIES:USE_libgcrypt_capabilities = "--with-capabilities"

FILES_${PN}-dev += "${bindir}/dumpsexp ${bindir}/hmac256"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "dumpsexp hmac256"

DEPENDS_${PN}-dumpsexp += "libc libcap"
RDEPENDS_${PN}-dumpsexp += "libc libcap"
DEPENDS_${PN}-hmac256 += "libc libcap"
RDEPENDS_${PN}-hmac256 += "libc libcap"
