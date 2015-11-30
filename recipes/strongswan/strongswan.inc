DESCRIPTION = "strongSwan is an OpenSource IPsec implementation for the \
Linux operating system."
HOMEPAGE = "http://www.strongswan.org"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://download.strongswan.org/strongswan-${PV}.tar.bz2"

DEPENDS = "libdl libm libpthread librt libcrypto libssl libgmp"

EXTRA_OECONF = "--disable-curl --disable-soup --disable-ldap --enable-gmp \
	--disable-mysql --disable-sqlite --enable-openssl"

EXTRA_OECONF += "--with-ipseclibdir=${libdir} \
       --with-plugindir=${libdir}/ipsec/plugins \
       --with-imcvdir=${libdir}/ipsec/imcvs \
"

inherit autotools

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "strongswan hydra charon"
LIBRARY_VERSION = "0"
DEPENDS_${PN}-libstrongswan = "libc libdl libpthread"
RDEPENDS_${PN}-libstrongswan = "libc libdl libpthread"
DEPENDS_${PN}-libhydra = "libc libstrongswan"
RDEPENDS_${PN}-libhydra = "libc libstrongswan"
DEPENDS_${PN}-libcharon = "libc libdl libm libpthread libstrongswan libhydra"
RDEPENDS_${PN}-libcharon = "libc libdl libm libpthread libstrongswan libhydra"

PACKAGEQA_HOST_BINDIRS += "${bindir}/ipsec"
FILES_${PN}-dev += "${libdir}/ipsec/plugins/*.a ${libdir}/ipsec/plugins/*.la"
FILES_${PN}-dbg += "${libdir}/ipsec/plugins/.debug ${libexecdir}/ipsec/.debug"
FILES_${PN} += "${libdir}/ipsec"
DEPENDS_${PN} += "libc libdl libm libpthread librt libgmp libcrypto \
	libstrongswan libhydra libcharon"
RDEPENDS_${PN} = "libc libdl libm libpthread librt libgmp libcrypto \
	libstrongswan libhydra libcharon"

do_install[postfuncs] =+ "do_install_extra_files"
do_install_extra_files() {
	sysvinit_install_script ${D}/usr/sbin/ipsec ipsec
}

inherit sysvinit
RECIPE_FLAGS += "strongswan_sysvinit_start strongswan_sysvinit_stop"
SYSVINIT_SCRIPT_strongswan = "ipsec"
DEFAULT_USE_strongswan_sysvinit_start = "0"
DEFAULT_USE_strongswan_sysvinit_stop  = "0"
