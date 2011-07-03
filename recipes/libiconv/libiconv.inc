# -*- mode:python; -*-
DESCRIPTION = "GNU libiconv - libiconv is for you if your application needs to \
	support multiple character encodings, but that support lacks from your \
	system."
HOMEPAGE = "http://www.gnu.org/software/libiconv"

RECIPE_TYPES = "machine native sdk"

SRC_URI = "ftp://ftp.gnu.org/pub/gnu/libiconv/libiconv-${PV}.tar.gz"

inherit autotools library auto-package-utils

EXTRA_OECONF += "--enable-shared --enable-static --enable-relocatable \
	--disable-rpath"

FILES_${PN} += "${libdir}/charset.alias"
PROVIDES_${PN} += "libcharset"
PROVIDES_${PN}-dev += "libcharset-dev"
AUTO_PACKAGE_UTILS = "iconv"
PROVIDES_${PN}-iconv = "${PN}-tools"
