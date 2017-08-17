DESCRIPTION = "skalibs is a package centralizing the free software / \
open source C development files used for building all software at skarnet.org"
LICENSE = "ISC"

require compatible-archs.inc

SRC_URI = "http://skarnet.org/software/${PN}/${PN}-${PV}.tar.gz"
RECIPE_TYPES = "machine native"

inherit c make

endianness = "${@['big', 'little'][d.get('HOST_ENDIAN') == 'l']}"
librt_flag = ""
librt_flag:native = "-lrt"

# All supported archs need to have a sysdeps and sysdeps.h file.  These are
# not provided by upstream, so we have to create them them ourselves when
# adding support for more archs.
SRC_URI += "file://sysdeps file://sysdeps.h"
do_configure[prefuncs] += "do_configure_sysdeps"
do_configure_sysdeps() {
	rm -rf ${B}/sysdeps
	mkdir -p ${B}/sysdeps
	echo "${librt_flag}" > ${B}/sysdeps/rt.lib
	echo "" > ${B}/sysdeps/socket.lib
	echo "" > ${B}/sysdeps/sysclock.lib
	echo "" > ${B}/sysdeps/tainnow.lib
	echo "" > ${B}/sysdeps/util.lib
	echo "${HOST_ARCH}" > ${B}/sysdeps/target
	cp ${SRCDIR}/sysdeps ${SRCDIR}/sysdeps.h ${B}/sysdeps/

	sed -e 's/^\(target\):. */\1: ${HOST_ARCH}/' \
	    -e 's/^\(endianness\): .*/\1: ${endianness}/' \
	    -i ${B}/sysdeps/sysdeps
	sed -e 's/^\(#define SKALIBS_TARGET\) .*/\1 "${HOST_ARCH}"/' \
	    -e 's/^\(#define SKALIBS_ENDIANNESS\) .*/\1 "${endianness}"/' \
	    -i ${B}/sysdeps/sysdeps.h
}

RECIPE_FLAGS = "skalibs_ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"
EXTRA_OECONF_IPV6 = "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_skalibs_ipv6 = "--enable-ipv6"

do_configure() {
	./configure \
		--prefix=${prefix} \
		--dynlibdir=${sharedlibdir} \
		--libdir=${libdir} \
		--includedir=${includedir} \
		--datadir=${datadir} \
		--sysdepdir=${libdir}/skalibs/sysdeps \
		--with-sysdeps=${B}/sysdeps \
		--enable-clock \
		--enable-monotonic \
		--with-default-path="${base_sbindir}:${sbindir}:${base_bindir}:${bindir}" \
		${HOST_ARCH}
}

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}"
FILES_${PN}-dev += "${libdir}/skalibs/sysdeps"

inherit library
LIBRARY_NAME = "libskarnet"
LIBRARY_VERSION = "2"

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
