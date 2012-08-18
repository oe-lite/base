DESCRIPTION = "Lua is a powerful light-weight programming language designed \
for extending applications."
LICENSE = "zlib/libpng License, MIT License, GNU Library or Lesser General Public License (LGPL)"
#check http://sourceforge.net/projects/luacheia/develop/
HOMEPAGE = "http://www.lua.org/"

inherit autotools

DEPENDS += "libm libdl readline"

require conf/fetch/sourceforge.conf
SRC_URI = "${SOURCEFORGE_MIRROR}/luacheia/luacheia5-${PV}.tar.gz"
S = "${SRCDIR}/luacheia5-${PV}"

SRC_URI += "file://autotoolsfixup.patch"

MODULELIST="bit,cgi,fs,fuzzy,gluahost,mapm,md5,pack,pcre,posix,rex,socket"
EXTRA_OECONF += "--with-lua-srcdir=${S}/lua-5.0.1/ \
	--enable-modules=${MODULELIST} \
	--prefix=${prefix} \
	--bindir=${bindir} \
	--sbindir=${sbindir} \
	--libexecdir=${libexecdir} \
	--datadir=${datadir} \
	--sysconfdir=${sysconfdir} \
	--libdir=${libdir} \
	--includedir=${includedir}"

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
