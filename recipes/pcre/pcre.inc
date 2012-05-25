# -*- mode:python; -*-
DESCRIPTION = """Perl-compatible regular expression library. PCRE has
its own native API, but a set of 'wrapper' functions that are based
on the POSIX API are also supplied in the library libpcreposix. Note
that this just provides a POSIX calling interface to PCRE; the
regular expressions themselves still follow Perl syntax and
semantics. The header file for the POSIX-style functions is called
pcreposix.h."""
HOMEPAGE = "http://www.pcre.org/"

RECIPE_TYPES = "native machine sdk"

inherit c++ autotools-autoreconf binconfig pkgconfig

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/project/${PN}/${PN}/${PV}/${P}.tar.gz"

DEPENDS = "libbz2 libz libreadline"

CFLAGS += "-D_REENTRANT"
EXTRA_OECONF = "--with-link-size=2 \
	--enable-newline-is-lf \
	--with-match-limit=10000000 \
	--enable-rebuild-chartables \
	--enable-utf8"

RECIPE_FLAGS += "pcre_utf8"
EXTRA_OECONF_UTF8 = "--disable-utf8"
EXTRA_OECONF_UTF8:USE_pcre_utf8 = "--enable-utf8"
EXTRA_OECONF += "${EXTRA_OECONF_UTF8}"

do_compile () {
	oe_runmake \
		CC_FOR_BUILD="${BUILD_CC}" \
		CFLAGS_FOR_BUILD="-DLINK_SIZE=2 -I${S}/include" \
		LINK_FOR_BUILD="${BUILD_CC} -L${S}/lib"
}

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "pcregrep pcretest"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "pcrecpp pcreposix pcre"
AUTO_PACKAGE_LIBS_PCPREFIX = "lib"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
DEPENDS_${PN}-libpcreposix = "libpcre libc"
DEPENDS_${PN}-libpcrecpp = "libpcre libc libm libgcc libstdc++"
