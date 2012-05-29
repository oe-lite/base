# -*- mode:python; -*-
DESCRIPTION = "The GNU internationalization library."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"

RECIPE_TYPES = "machine native sdk"

inherit autotools-autoreconf make-vpath

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz"

DEPENDS = "libiconv libncurses libdl libm libpthread ${DEPENDS_SELF_NATIVE}"
DEPENDS_SELF_NATIVE = "native:gettext"
DEPENDS_SELF_NATIVE:native = ""

acpaths = "-I ${S}/gnulib-local/m4/ \
           -I ${S}/gettext-runtime/m4 \
           -I ${S}/gettext-tools/m4"

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
--with-included-libxml \
--with-included-libunistring \
--with-included-libcroco \
--without-emacs --without-git --without-cvs \
--with-included-glib \
"
EXTRA_OECONF:>native = " --disable-curses --with-included-gettext"

FILES_${PN} += "${libdir}/gettext ${datadir}/gettext"

DEPENDS_${PN} = "libintl libgettextpo libgettextlib \
    libiconv libncurses libdl libm"
RDEPENDS_${PN} = "${DEPENDS_${PN}}"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "intl gettextpo gettextlib gettextsrc"
FILES_${PN}-libintl = "${libdir}/preloadable_libintl.so"
FILES_${PN}-libgettextlib = "${libdir}/libgettextlib-*.so"
FILES_${PN}-libgettextsrc = "${libdir}/libgettextsrc-*.so"

DEPENDS_${PN}-libgettextpo = "libiconv"
DEPENDS_${PN}-libgettextlib = "libiconv libncurses"
DEPENDS_${PN}-libgettextsrc = "libgettextlib libiconv libncurses libdl libm"
