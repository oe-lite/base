# -*- mode:python; -*-
DESCRIPTION = "LibreSSL is a version of the TLS/crypto stack forked from OpenSSL in 2014, \
	       with goals of modernizing the codebase, improving security, \
	       and applying best practice development processes."

HOMEPAGE = "http://www.libressl.org/"
LICENSE = "openssl"

RECIPE_TYPES = "machine native sdk"

inherit c make pkgconfig autotools

SRC_URI = "http://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-${PV}.tar.gz"

DEPENDS = "${DEPENDS_HOST_OS} libc libgcc"
DEPENDS_HOST_OS = "libdl"
DEPENDS_HOST_OS:HOST_OS_mingw32 = ""

DEPENDS_${PN} += " ${PN}-libcrypto ${PN}-libssl ${PN}-libtls"
RDEPENDS_${PN} += " ${PN}-libcrypto ${PN}-libssl ${PN}-libtls ${PN}-engines ${PN}-misc"

PACKAGES =+ "${PN}-misc ${PN}-engines"
FILES_${PN}-misc = "${libdir}/ssl/misc ${libdir}/ssl/openssl.cnf"
FILES_${PN}-doc =+ "${libdir}/ssl/man"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "crypto ssl tls"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "openssl c_rehash"
DEPENDS_${PN}-openssl += "libc libdl libcrypto libssl"
RDEPENDS_${PN}-openssl += "libc libdl libcrypto libssl"
DEPENDS_${PN}-dev = ""
FILES_${PN}-libcrypto += " ${LIBCRYPTO_FILES}"  
LIBCRYPTO_FILES = ""
LIBCRYPTO_FILES:HOST_OS_mingw32 = "${sharedlibdir}/libeay32.dll"
FILES_${PN}-libssl += " ${LIBSSL_FILES}"
LIBSSL_FILES = ""
LIBSSL_FILES:HOST_OS_mingw32 = "${sharedlibdir}/ssleay32.dll"
DEPENDS_${PN}-libcrypto += " ${DEPENDS}"
DEPENDS_${PN}-libssl += " ${DEPENDS} libcrypto"
RDEPENDS_${PN}-libcrypto += "libc libgcc ${DEPENDS_HOST_OS}"
RDEPENDS_${PN}-libssl += "${DEPENDS_HOST_OS} libcrypto"
DEPENDS_${PN}-libtls += "${DEPENDS} libcrypto libssl"
RDEPENDS_${PN}-libtls += "${DEPENDS_HOST_OS} libcrypto libssl"

PRIORITY = "-1"
