DESCRIPTION = "A general purpose cryptographic library based on the code from GnuPG"
HOMEPAGE = "http://directory.fsf.org/project/libgcrypt/"

inherit autotools-autoreconf binconfig pkgconfig library

DEPENDS = "libgpg-error libcap2"
DEPENDS_${PN} += "libgpg-error libcap2"

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/libgcrypt/libgcrypt-${PV}.tar.gz"

RECIPE_FLAGS = "libgcrypt_capabilities"
DEFAULT_USE_libgcrypt_capabilities = "1"

EXTRA_OECONF = "--without-pth --disable-asm ${EXTRA_OECONF_CAPABILITIES}"
EXTRA_OECONF_CAPABILITIES = "--without-capabilities"
EXTRA_OECONF_CAPABILITIES:USE_libgcrypt_capabilities = "--with-capabilities"

# libgcrypt.pc is added locally and thus installed here
do_install[postfuncs] += "do_install_append"
do_install_append() {
	install -d ${D}/${libdir}/pkgconfig
	install -m 0644 ${S}/src/libgcrypt.pc ${D}/${libdir}/pkgconfig/
}

FILES_${PN}-dev += "${bindir}/dumpsexp ${bindir}/hmac256"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "dumpsexp hmac256"
