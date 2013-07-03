# -*- mode:python; -*-

DESCRIPTION = "Userspace implementation of a splash screen for Linux systems"
HOMEPAGE = "http://fbsplash.alanhaggai.org/index.html"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools-autoreconf pkgconfig binconfig

SRC_URI = "http://fbsplash.alanhaggai.org/tarballs/files/splashutils-lite-${PV}.tar.bz2"

DEPENDS = "libpthread librt libm libz libjpeg libpng12 libfreetype"

# distclean goes into infinite loop checking for dirs in libs/ :-(
AUTOTOOLS_DISTCLEAN = "0"

EXTRA_OECONF += "--disable-helper"
EXTRA_OECONF += "--without-klibc"
EXTRA_OECONF += "--without-gpm"

EXTRA_OECONF += "--without-freetype2-src"
EXTRA_OECONF += "--without-jpeg-src"
EXTRA_OECONF += "--without-lpng-src"
EXTRA_OECONF += "--without-zlib-src"

RECIPE_FLAGS += "splashutils_png"
DEFAULT_USE_splashutils_png = "1"
DEPENDS += "${DEPENDS_PNG}"
DEPENDS_PNG = ""
DEPENDS_PNG:USE_splashutils_png = "libpng12"
EXTRA_OECONF += "${EXTRA_OECONF_PNG}"
EXTRA_OECONF_PNG = " --without-png"
EXTRA_OECONF_PNG:USE_splashutils_png = ""

PACKAGES =+ "${PN}-splash-functions"
FILES_${PN}-splash-functions = "${base_sbindir}/splash-functions.sh"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "fbsplash fbsplashrender"
AUTO_PACKAGE_LIBS_PCPREFIX = "lib"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
DEPENDS_${PN}-libfbsplashrender = "libm libz libjpeg libpng12 libfreetype libgcc libc"
RDEPENDS_${PN}-libfbsplashrender = "libm libz libjpeg libpng12 libfreetype libgcc libc"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "fbsplashd splash_util fbcondecor_ctl fbsplashctl \
	bootsplash2fbsplash splash_manager splash_resize"
FILES_${PN}-fbsplashctl = "${base_sbindir}/*.static"
RDEPENDS_${PN}-fbsplashd = "libfbsplashrender libfbsplash libjpeg libc \
	libpng12 libz libgcc libm libfreetype libpthread librt"
RDEPENDS_${PN}-splash-util = "libfbsplashrender libfbsplash libjpeg \
	libc libpng12 libz libgcc libm libfreetype"
RDEPENDS_${PN}-fbcondecor_ctl = "libfbsplashrender libfbsplash libjpeg \
	libc libpng12 libz libgcc libm libfreetype"

do_install_cachedir () {
	install -d ${D}${base_libdir}/splash/cache
}
do_install[postfuncs] += "do_install_cachedir"
FILES_${PN}-fbsplashctl += "${base_libdir}/splash/cache"

MIRRORS = """
http://fbsplash.alanhaggai.org/tarballs/files http://sourceforge.net/projects/fbsplash.berlios/files/
"""
