DESCRIPTION = "GNU Transport Layer Security Library"
HOMEPAGE = "http://www.gnu.org/software/gnutls/"
BUGTRACKER = "https://savannah.gnu.org/support/?group=gnutls"

inherit c++ autotools-autoreconf binconfig pkgconfig gettext

DEPENDS += "libz liblzo libtasn1 libgcrypt libreadline"
DEPENDS_${PN} += "libz liblzo libtasn1 libgcrypt libreadline"
RDEPENDS_${PN} += "gnutls-extra liblzo libtasn1"

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
AUTO_PACKAGE_LIBS = "gnutls gnutlsxx gnutls-openssl gnutls-extra"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev"
RDEPENDS_${PN}-libgnutls-extra += "libtasn1 liblzo"
RDEPENDS_${PN}-libgnutls += "libtasn1"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "srptool certtool gnutls-serv psktool gnutls-cli \
	gnutls-cli-debug"
