DESCRIPTION = "A library for configuring and customizing font access."

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools pkgconfig c++ library

DEPENDS = "libexpat libfreetype libz"

SRC_URI = "http://fontconfig.org/release/${PN}-${PV}.tar.gz"

S = "${SRCDIR}/${PN}-${PV}"

EXTRA_OECONF = "--disable-docs --with-arch=${HOST_ARCH}"

RECIPE_FLAGS += "fontconfig_cache_dir"
DEFAULT_USE_fontconfig_cache_dir = "${localstatedir}/lib/${PN}"
EXTRA_OECONF_cache_dir = ""
EXTRA_OECONF_cache_dir:USE_fontconfig_dir_cache = "--with-cache-dir=${USE_fontconfig_dir_cache}"
EXTRA_OECONF += "${EXTRA_OECONF_cache_dir}"

RECIPE_FLAGS += "fontconfig_fonts_dir"
EXTRA_OECONF_fonts_dir = ""
EXTRA_OECONF_fonts_dir:USE_fontconfig_fonts_dir = "--with-default-fonts=${USE_fontconfig_fonts_dir}"
EXTRA_OECONF += "${EXTRA_OECONF_fonts_dir}"

do_configure_extra_MAKEFILES = "fc-case/Makefile fc-glyphname/Makefile \
	fc-lang/Makefile fc-arch/Makefile"

do_configure[postfuncs] += "do_configure_extra"
do_configure_extra () {
	for makefile in ${do_configure_extra_MAKEFILES}
	do
		sed -i -e 's|^LDFLAGS =.*|LDFLAGS =${BUILD_LDFLAGS}|' \
		       -e 's|^CFLAGS =.*|CFLAGS =${BUILD_CFLAGS}|' \
		       -e 's|^CPPFLAGS =.*|CPPFLAGS =${BUILD_CPPFLAGS}|' \
		       -e 's|^CXXFLAGS =.*|CFLAGS =${BUILD_CXXFLAGS}|' \
		       $makefile
	done
}

EXTRA_OEMAKE = "FC_LANG=fc-lang FC_GLYPHNAME=fc-glyphname"
export HASDOCBOOK="no"

PACKAGES =+ "${PN}-utils-dbg ${PN}-utils "
RECIPE_TYPES = "machine native"

FILES_${PN}-utils-dbg = "${bindir}/.debug/*"
FILES_${PN}-utils = "${bindir}/fc*"
FILES_${PN} += "${sysconfdir}/fonts"
FILES_${PN} += "${datadir}/fontconfig"
FILES_${PN} += "${datadir}/xml"

DEPENDS_${PN} += "libexpat libfreetype libz libc libgcc"
RDEPENDS_${PN} += "libexpat libfreetype libz libc libgcc"
DEPENDS_${PN}-utils += "libfontconfig libexpat libfreetype libz libc libgcc"
RDEPENDS_${PN}-utils += "libfontconfig libexpat libfreetype libz libc libgcc"
