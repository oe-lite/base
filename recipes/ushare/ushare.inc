inherit make c pkgconfig sysvinit

COMPATIBLE_HOST_ARCHS = ".*linux"

RECIPE_FLAGS = "ushare_sysvinit_start ushare_sysvinit_stop"
DEFAULT_USE_ushare_sysvinit_start	= "70"
DEFAULT_USE_ushare_sysvinit_stop	= "0"
SYSVINIT_SCRIPT_ushare		        = "ushare"

DEPENDS = "libupnp libupnp-dev"
RDEPENDS_${PN} = "libupnp"

SRC_URI = "http://ushare.geexbox.org/releases/ushare-${PV}.tar.bz2"
SRC_URI += "file://init-script.patch"
SRC_URI += "file://gcc5.patch"

#ushare is old. autotools class does not work with this old configure script,
#so we do it manually
do_configure() {
 cd ${S}
 ./configure --cross-compile --cross-prefix=${CROSS} --prefix=/ --with-libupnp-dir=${HOST_SYSROOT}${libdir}
}

do_install[postfuncs] = "do_install_rm_locales"

do_install_rm_locales() {
  rm -rf ${D}/share/locale
}
