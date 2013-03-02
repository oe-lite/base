# -*- mode:python; -*-
DESCRIPTION = "The GNU internationalization library."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"

RECIPE_TYPES = "machine native sdk"

inherit c++ autotools-autoreconf library make-vpath

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz"

DEPENDS = "libiconv ${DEPENDS_HOST_OS} ${DEPENDS_SELF_NATIVE}"
DEPENDS_HOST_OS = "libdl libpthread libm libncurses"
DEPENDS_HOST_OS:HOST_OS_mingw32 = "libm libncurses"
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
EXTRA_OECONF += "${EXTRA_OECONF_GETTEXT}"
EXTRA_OECONF_GETTEXT = ""
EXTRA_OECONF_GETTEXT:native = "--disable-curses --with-included-gettext"
EXTRA_OECONF_GETTEXT:HOST_OS_mingw32 = "--with-included-gettext"

DEPENDS_${PN} = "libintl libgettextpo libgettextlib \
    libiconv libncurses libdl libm"
RDEPENDS_${PN} = "${DEPENDS_${PN}}"

PACKAGES =+ "${PN}-utils"
FILES_${PN} += "${libdir}/gettext ${datadir}/gettext"
FILES_${PN}-utils = "${bindir}/*"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "intl gettextpo gettextlib gettextsrc"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
DEPENDS_${PN}-libintl += "libiconv"
DEPENDS_${PN}-libgettextpo += "libiconv"
DEPENDS_${PN}-libgettextlib += "libiconv libncurses"
DEPENDS_${PN}-libgettextsrc += "libgettextlib libiconv libncurses libdl libm"
FILES_${PN}-libintl += "${sharedlibdir}/preloadable_libintl${SOLIBSDEV}"
FILES_${PN}-libgettextlib += "${sharedlibdir}/libgettextlib${SOLIBSDEV}"
FILES_${PN}-libgettextsrc += "${sharedlibdir}/libgettextsrc${SOLIBSDEV}"
