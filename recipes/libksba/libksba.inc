SUMMARY = "Easy API to create and parse X.509 and CMS related objects"
HOMEPAGE = "http://www.gnupg.org/related_software/libksba/"
LICENSE = "GPLv2+ | LGPLv3+ | GPLv3+"

DEPENDS = "libgpg-error"

inherit autotools-autoreconf pkgconfig library auto-package-utils binconfig

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/${PN}/${PN}-${PV}.tar.bz2"

AUTO_PACKAGE_UTILS += "ksba-config"

DEPENDS_${PN} += "libgpg-error libc"
RDEPENDS_${PN} += "libgpg-error libc"
