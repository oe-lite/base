SUMMARY = "Utilities for extracting and viewing files in .zip archives"
HOMEPAGE = "http://www.info-zip.org"
LICENSE = "BSD-3-Clause"

RECIPE_TYPES = "machine native sdk"
COMPATIBLE_HOST_ARCHS = ".*linux"
inherit c make auto-package-utils

SRC_URI = "ftp://ftp.info-zip.org/pub/infozip/src/unzip60.tgz \
file://avoid-strip.patch \
file://define-ldflags.patch \
file://06-unzip60-alt-iconv-utf8_CVE-2015-1315.patch \
file://cve-2014-9636.patch \
file://09-cve-2014-8139-crc-overflow.patch \
file://10-cve-2014-8140-test-compr-eb.patch \
file://11-cve-2014-8141-getzip64data.patch \
file://CVE-2015-7696.patch \
file://CVE-2015-7697.patch \
"
S = "${SRCDIR}/unzip60"

EXTRA_OEMAKE += "STRIP=true"

do_configure() {
    cat <<EOF > flags
CC="${CC}" CF="-DUNIX -I. ${CFLAGS} -DLARGE_FILE_SUPPORT -DUNICODE_SUPPORT -DUNICODE_WCHAR -DHAVE_DIRENT_H -DHAVE_TERMIOS_H -DNO_LCHMOD -D_MBCS " CRCA_O="" AS="${AS}" LFLAGS1="${LDFLAGS}" LF2="" CC_BZ="${CC}" CFLAGS_BZ="" IZ_BZIP2="." D_USE_BZ2="" L_BZ2="" LIBBZ2=""
EOF
}

do_compile() {
    oe_runmake -f unix/Makefile generic
}

do_install() {
    oe_runmake -f unix/Makefile install prefix=${D}${prefix}
    install -d ${D}${mandir}
    mv ${D}${prefix}/man/* ${D}${mandir}
    rmdir ${D}${prefix}/man/
}

AUTO_PACKAGE_UTILS = "unzip funzip unzipsfx zipgrep zipinfo"
AUTO_PACKAGE_UTILS_DEPENDS = "libc"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc"
RDEPENDS_${PN}-zipgrep += "${PN}-unzip"
RDEPENDS_${PN} += "${PN}-unzip"
