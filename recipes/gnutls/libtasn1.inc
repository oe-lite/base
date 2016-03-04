DESCRIPTION = "Library for ASN.1 and DER manipulation"
HOMEPAGE = "http://www.gnu.org/software/libtasn1/"

LICENSE = "GPL-3.0+ & LGPL-2.1+"
LICENSE_${PN}-bin = "GPL-3.0+"
LICENSE_${PN} = "LGPL-2.1+"

COMPATIBLE_HOST_ARCHS = ".*linux"

require conf/fetch/gnu.conf

SRC_URI = "${GNU_MIRROR}/libtasn1/libtasn1-${PV}.tar.gz"

inherit autotools-autoreconf binconfig package library

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "asn1Coding asn1Decoding asn1Parser"
DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
AUTO_PACKAGE_UTILS_DEPENDS = "libc libtasn1"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libtasn1"

do_patch[postfuncs] += "do_patch_nodocu"
do_patch_nodocu(){
	rm -rf ${S}/doc -rf
	sed 's/ doc//' -i ${S}/Makefile.am
	sed '/doc\//d' -i ${S}/configure.ac
}
