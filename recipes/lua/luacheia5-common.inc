DESCRIPTION = "Lua is a powerful light-weight programming language designed \
for extending applications."
LICENSE = "zlib/libpng License, MIT License, GNU Library or Lesser General Public License (LGPL)"
#check http://sourceforge.net/projects/luacheia/develop/
HOMEPAGE = "http://www.lua.org/"

inherit autotools-autoreconf

DEPENDS += "libm libdl readline"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/luacheia/luacheia5-${PV}.tar.gz"
S = "${SRCDIR}/luacheia5-${PV}"

SRC_URI += "file://autotoolsfixup.patch"

do_patch[postfuncs] += "do_patch_pkgdata_fixup"
do_patch_pkgdata_fixup() {
	fgrep -rlZ pkglib_DATA --include Makefile.am ${S} | \
		xargs -0 sed -i 's/pkglib_DATA/pkgdata_DATA/g'
}

MODULELIST="bit,cgi,fs,fuzzy,gluahost,mapm,md5,pack,pcre,posix,rex,socket"
EXTRA_OECONF += "--with-lua-srcdir=${S}/lua-5.0.1/ \
	--enable-modules=${MODULELIST} \
"

# Disable SDL for now, as we don't have an SDL recipe yet
EXTRA_OECONF_SDL = "ac_cv_path_SDL_CONFIG=no"
EXTRA_OECONF += "${EXTRA_OECONF_SDL}"

do_compile[prefuncs] += "do_compile_replace_clc_tck"
do_compile_replace_clc_tck() {
	sed -i -e 's/\/CLK_TCK/\/CLOCKS_PER_SEC/' ${S}/src/modules/posix/lposix.c
	sed -i -e 's/\/CLK_TCK/\/CLOCKS_PER_SEC/' ${S}/src/modules/socket/timeout.c
}

do_compile() {
	make
}

do_install() {
	make install DESTDIR=${D}
}
