DESCRIPTION = "A library for configuring and customizing font access."
LICENSE = "BSD"
DEPENDS = "expat-dev freetype-dev libz"

inherit autotools pkgconfig

SRC_URI = "http://fontconfig.org/release/fontconfig-${PV}.tar.gz"

S = "${SRCDIR}/fontconfig-${PV}"

EXTRA_OECONF = " --disable-docs --with-arch=${HOST_ARCH} --with-cache-dir=/var/lib/fontconfig"
do_configure_append () {
        sed -i 's|LDFLAGS =.*|LDFLAGS =|' fc-case/Makefile
        sed -i 's|LDFLAGS =.*|LDFLAGS =|' fc-glyphname/Makefile
        sed -i 's|LDFLAGS =.*|LDFLAGS =|' fc-lang/Makefile
        sed -i 's|LDFLAGS =.*|LDFLAGS =|' fc-arch/Makefile
        sed -i 's|CFLAGS =.*|CFLAGS =${BUILD_CFLAGS}|' fc-case/Makefile
        sed -i 's|CFLAGS =.*|CFLAGS =${BUILD_CFLAGS}|' fc-glyphname/Makefile
        sed -i 's|CFLAGS =.*|CFLAGS =${BUILD_CFLAGS}|' fc-lang/Makefile
        sed -i 's|CFLAGS =.*|CFLAGS =${BUILD_CFLAGS}|' fc-arch/Makefile
        sed -i 's|CPPFLAGS =.*|CPPFLAGS =${BUILD_CPPFLAGS}|' fc-case/Makefile
        sed -i 's|CPPFLAGS =.*|CPPFLAGS =${BUILD_CPPFLAGS}|' fc-glyphname/Makefile
        sed -i 's|CPPFLAGS =.*|CPPFLAGS =${BUILD_CPPFLAGS}|' fc-lang/Makefile
        sed -i 's|CPPFLAGS =.*|CPPFLAGS =${BUILD_CPPFLAGS}|' fc-arch/Makefile
        sed -i 's|CXXFLAGS =.*|CFLAGS =${BUILD_CXXFLAGS}|' fc-case/Makefile
        sed -i 's|CXXFLAGS =.*|CFLAGS =${BUILD_CXXFLAGS}|' fc-glyphname/Makefile
        sed -i 's|CXXFLAGS =.*|CFLAGS =${BUILD_CXXFLAGS}|' fc-lang/Makefile
        sed -i 's|CXXFLAGS =.*|CFLAGS =${BUILD_CXXFLAGS}|' fc-arch/Makefile
}

EXTRA_OEMAKE = "FC_LANG=fc-lang FC_GLYPHNAME=fc-glyphname"
export HASDOCBOOK="no"
BUILD_CFLAGS += " -I${STAGE_DIR}/sysroot/include/freetype2"

PACKAGES =+ "fontconfig-utils-dbg fontconfig-utils "

FILES_fontconfig-utils-dbg = "${bindir}/*.dbg"
FILES_fontconfig-utils = "${bindir}/*"
