DESCRIPTION = "The GNU internationalization library."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"
LICENSE = "GPLv3"

BBCLASSEXTEND = "native sdk"

DEPENDS = "libiconv${RE}-dev ncurses${RE}-dev"
DEPENDS =+ "${SYSROOT_DEPENDS}"
SYSROOT_DEPENDS = "\
	${HOST_ARCH}/sysroot-libdl \
	${HOST_ARCH}/sysroot-libm \
	${HOST_ARCH}/sysroot-libpthread \
"
SYSROOT_DEPENDS_recipe-native = ""

PACKAGES =+ "\
    ${PN}-libintl-dev ${PN}-libintl \
    ${PN}-libgettextpo-dev  ${PN}-libgettextpo \
    ${PN}-libgettextlib-dev ${PN}-libgettextlib \
    ${PN}-libgettextsrc-dev ${PN}-libgettextsrc"

DEPENDS_${PN} = "${PN}-dev ${RDEPENDS_${PN}}"
DEPENDS_${PN}-dev = ""
RDEPENDS_${PN}-dev = ""
RDEPENDS_${PN} = "\
    ${PN}-libintl ${PN}-libgettextpo ${PN}-libgettextlib ${PN}-libgettextsrc \
    libiconv${RE} libncurses${RE} \
    ${HOST_ARCH}/sysroot-libdl ${HOST_ARCH}/sysroot-libm"

RPROVIDES_${PN}-libintl = "${PN}-libintl libintl${RE}"
RPROVIDES_${PN}-libgettextpo = "${PN}-libgettextpo libgettextpo${RE}"
RPROVIDES_${PN}-libgettextlib = "${PN}-libgettextlib libgettextlib${RE}"
RPROVIDES_${PN}-libgettextsrc = "${PN}-libgettextsrc libgettextsrc${RE}"

PROVIDES_${PN}-libintl = "${PN}-libintl libintl${RE}"
PROVIDES_${PN}-libgettextpo = "${PN}-libgettextpo libgettextpo${RE}"
PROVIDES_${PN}-libgettextlib = "${PN}-libgettextlib libgettextlib${RE}"
PROVIDES_${PN}-libgettextsrc = "${PN}-libgettextsrc libgettextsrc${RE}"

DEPENDS_${PN}-libintl = "${RDEPENDS_${PN}-libintl} ${PN}-dev"
RDEPENDS_${PN}-libintl = ""

DEPENDS_${PN}-libgettextpo = "${RDEPENDS_${PN}-libgettextpo} ${PN}-dev"
RDEPENDS_${PN}-libgettextpo = "libiconv${RE}"

DEPENDS_${PN}-libgettextlib = "${RDEPENDS_${PN}-libgettextlib} ${PN}-dev"
RDEPENDS_${PN}-libgettextlib = "libiconv${RE} libncurses${RE}"

DEPENDS_${PN}-libgettextsrc = "${RDEPENDS_${PN}-libgettextsrc} ${PN}-dev"
RDEPENDS_${PN}-libgettextsrc = "${PN}-libgettextlib \
    libiconv${RE} libncurses${RE} \
    ${HOST_ARCH}/sysroot-libm ${HOST_ARCH}/sysroot-libdl"


require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz"

inherit autotools

AUTOTOOLS_AUTORECONF = "1"
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
--with-included-gettext \
--with-included-libxml \
--with-included-libunistring \
--with-included-libcroco \
--with-included-glib \
--without-emacs --without-git --without-cvs \
--with-included-glib \
"

FILES_${PN} += "${libdir}/gettext ${datadir}/gettext"

FILES_${PN}-libintl = "${libdir}/libintl*.so.*"
FILES_${PN}-libintl-dev = "${libdir}/libintl.la"

FILES_${PN}-libgettextlib = "${libdir}/libgettextlib-*.so*"
FILES_${PN}-libgettextlib-dev = "${libdir}/libgettextlib.la ${libdir}/libgettextlib.a ${libdir}/libgettextlib.so"

FILES_${PN}-libgettextsrc = "${libdir}/libgettextsrc-*.so*"
FILES_${PN}-libgettextsrc-dev = "${libdir}/libgettextsrc.la ${libdir}/libgettextsrc.a ${libdir}/libgettextsrc.so"

FILES_${PN}-libgettextpo = "${libdir}/libgettextpo-*.so*"
FILES_${PN}-libgettextpo-dev = "${libdir}/libgettextpo.la ${libdir}/libgettextpo.a ${libdir}/libgettextpo.so"
