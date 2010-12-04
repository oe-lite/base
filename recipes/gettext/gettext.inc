DESCRIPTION = "The GNU internationalization library."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"
SECTION = "libs"
LICENSE = "GPLv3"

PR = "r1"

BBCLASSEXTEND = "native sdk"

DEPENDS = "libiconv${RE}-dev ncurses${RE}-dev expat${RE}-dev"
DEPENDS =+ "${EXTRA_DEPENDS}"
EXTRA_DEPENDS = "\
	${TARGET_ARCH}/sysroot-libdl \
	${TARGET_ARCH}/sysroot-libpthread \
	${TARGET_ARCH}/sysroot-libm \
	gettext-native"
EXTRA_DEPENDS_recipe-native = ""

PACKAGES =+ "${PN}-libintl ${PN}-libgettextlib ${PN}-libgettextsrc"

RPROVIDES_${PN}-libintl = "libintl${RE}"
RPROVIDES_${PN}-libgettextlib = "libgettextlib${RE}"
RPROVIDES_${PN}-libgettextsrc = "libgettextsrc${RE}"
PROVIDES_${PN}-dev = "libintl${RE} libgettextlib${RE} libgettextsrc${RE}"
DEPENDS_${PN}-dev = "${PN}-libintl ${PN}-libgettextsrc ${PN}-libgettextlib"

RDEPENDS_${PN} = "${PN}-libgettextlib ${PN}-libgettextsrc \
	libiconv${RE} libncurses${RE} ${HOST_ARCH}/sysroot-libm"
DEPENDS_${PN}-libgettextsrc = "${RDEPENDS_${PN}-libggettextsrc}
RDEPENDS_${PN}-libgettextsrc = "${PN}-libgettextlib \
	libiconv${RE} libncurses${RE}"
DEPENDS_${PN}-libgettextlib = "${RDEPENDS_${PN}-libggettextlib}
RDEPENDS_${PN}-libgettextlib = "libiconv${RE} libncurses${RE}"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz"

PARALLEL_MAKE = ""

inherit autotools

EXTRA_OECONF += "\
--disable-rpath --enable-relocatable \
--disable-dependency-tracking \
--disable-java --disable-native-java \
--disable-csharp \
--disable-nls \
--without-lispdir \
--disable-libasprintf \
--disable-acl \
--disable-openmp \
--disable-largefile \
--with-included-glib \
--without-emacs --without-git --without-cvs \
"

FILES_${PN} += "${libdir}/gettext ${datadir}/gettext"
FILES_${PN}-libintl = "${libdir}/libintl*.so.*"
FILES_${PN}-libgettextlib = "${libdir}/libgettextlib-*.so*"
FILES_${PN}-libgettextsrc = "${libdir}/libgettextsrc-*.so*"
