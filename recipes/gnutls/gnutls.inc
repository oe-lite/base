DESCRIPTION = "GNU Transport Layer Security Library"
HOMEPAGE = "http://www.gnu.org/software/gnutls/"
BUGTRACKER = "https://savannah.gnu.org/support/?group=gnutls"

COMPATIBLE_HOST_ARCHS = ".*linux"

LICENSE = "GPL-3.0+ & LGPL-2.1+"
LICENSE_${PN} = "LGPL-2.1+"
LICENSE_${PN}-xx = "LGPL-2.1+"
LICENSE_${PN}-bin = "GPL-3.0+"
LICENSE_${PN}-extra = "GPL-3.0+"
LICENSE_${PN}-openssl = "GPL-3.0+"

PARALLEL_MAKE = ""

inherit c++ autotools make-vpath binconfig pkgconfig gettext

DEPENDS += "libz liblzo2 ${DEPENDS_LIBTASN1} libgcrypt libreadline"
DEPENDS_LIBTASN1 ?= "libtasn1"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gnutls/gnutls-${PV}.tar.bz2"

EXTRA_OECONF="--with-included-opencdk --with-included-libcfg --disable-rpath \
              --with-libtasn1-prefix=${HOST_SYSROOT} \
              --with-libgcrypt --with-libgcrypt-prefix=${HOST_SYSROOT} \
              --with-libdl-prefix=${HOST_SYSROOT} \
              --with-libpthread-prefix=${HOST_SYSROOT} \
              --with-libreadline-prefix=${HOST_SYSROOT} \
              --with-libz-prefix=${HOST_SYSROOT} \
              --with-lzo --disable-guile \
              --without-p11-kit \
              "

CFLAGS += "-I${HOST_SYSROOT}${includedir}"

do_autoreconf[prefuncs] += "do_autoreconf_prepend"
do_autoreconf_prepend() {
	for dir in . lib libextra; do
		rm -f $dir/aclocal.m4 $dir/m4/libtool.m4 $dir/m4/lt*.m4
	done
}

do_stage[postfuncs] += "do_stage_fix_libstdc"
do_stage_fix_libstdc() {
	ln -sf ${HOST_SYSROOT}${libdir} ${HOST_SYSROOT}${libdir}/.libs
}

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "gnutls gnutlsxx gnutls-openssl"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
DEPENDS_${PN}-dev = ""
RDEPENDS_${PN}-libgnutls-extra += "${DEPENDS_LIBTASN1} liblzo2"
DEPENDS_${PN}-libgnutls += "libc libz ${DEPENDS_LIBTASN1} libgpg-error libgcrypt libiconv"
DEPENDS_${PN}-libgnutls += "libgmp libhogweed libnettle"
RDEPENDS_${PN}-libgnutls += "libc libz ${DEPENDS_LIBTASN1} libgpg-error libgcrypt libiconv"
RDEPENDS_${PN}-libgnutls += "libgmp libhogweed libnettle"
DEPENDS_${PN}-libgnutlsxx += "libgcc-s libc libm libstdc++  libgnutls"
RDEPENDS_${PN}-libgnutlsxx += "libgcc-s libc libm libstdc++  libgnutls"
DEPENDS_${PN}-libgnutls-openssl += "libc ${DEPENDS_LIBTASN1} libgnutls"
RDEPENDS_${PN}-libgnutls-openssl += "libc ${DEPENDS_LIBTASN1} libgnutls"
DEPENDS_${PN}-libgnutls-extra += "libc liblzo2 libgnutls libgpg-error libgcrypt"
RDEPENDS_${PN}-libgnutls-extra += "libc liblzo2 libgnutls libgpg-error libgcrypt"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "srptool certtool gnutls-serv psktool gnutls-cli \
	gnutls-cli-debug"
AUTO_PACKAGE_UTILS += "danetool ocsptool"
AUTO_PACKAGE_UTILS_DEPENDS += "libc libgnutls"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc libgnutls"
DEPENDS_${PN}-gnutls-serv += "libgnutls-extra"
RDEPENDS_${PN}-gnutls-serv += "libgnutls-extra"
DEPENDS_${PN}-gnutls-cli += "libgnutls-extra"
RDEPENDS_${PN}-gnutls-cli += "libgnutls-extra"

DEPENDS_${PN}-certtool += "libgmp libhogweed libnettle"
RDEPENDS_${PN}-certtool += "libgmp libhogweed libnettle"
