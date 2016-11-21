SUMMARY = "Easy API to create and parse X.509 and CMS related objects"
HOMEPAGE = "http://www.gnupg.org/related_software/libksba/"
LICENSE = "GPL-2.0+ | LGPL-3.0+ | GPL-3.0+"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "native machine sdk"

DEPENDS = "libgpg-error"

inherit autotools pkgconfig library auto-package-utils binconfig

SRC_URI = "ftp://ftp.gnupg.org/gcrypt/${PN}/${PN}-${PV}.tar.bz2"

AUTO_PACKAGE_UTILS += "ksba-config"

DEPENDS_${PN} += "libgpg-error libc"
RDEPENDS_${PN} += "libgpg-error libc"
