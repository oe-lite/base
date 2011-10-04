# -*- mode:python; -*-
DESCRIPTION = "Secure Socket Layer (SSL) binary and related \
	cryptographic tools."
HOMEPAGE = "http://www.openssl.org/"
LICENSE = "openssl"

RECIPE_TYPES = "machine native sdk"

inherit c make pkgconfig

SRC_URI = "http://www.openssl.org/source/openssl-${PV}.tar.gz"

DEPENDS = "libdl"

CFLAG = "${@['-DL_ENDIAN', '-DB_ENDIAN']['${TARGET_ENDIAN}'=='b']} -DTERMIO ${TARGET_CFLAGS}"

export DIRS = "crypto ssl apps engines"
export EX_LIBS = "-lgcc -ldl"
export AS = "${CC} -c"

do_configure () {
	cd util
	perl perlpath.pl ${bindir}
	cd ..
	ln -sf apps/openssl.pod crypto/crypto.pod ssl/ssl.pod doc/

	# FIXME: drop this silly case construction and use BB variable
	# overrides instead, which should improve build hashing effectiveness
	target="${TARGET_OS}-${TARGET_CPU}"
	case $target in
	linux-gnueabi-arm)
		target=linux-armv4
		;;
	linux-gnueabi-armeb)
		target=linux-elf-armeb
		;;
	linux-gnu-sh3)
		target=debian-sh3
		;;
	linux-gnu-sh4)
		target=debian-sh4
		;;
	linux-gnu-i486)
		target=debian-i386-i486
		;;
	linux-gnu-i586 | linux-gnu-viac3)
		target=debian-i386-i586
		;;
	linux-gnu-i686)
		target=debian-i386-i686/cmov
		;;
	linux-gnu-mips)
		target=debian-mips
		;;
	linux-gnu-mipsel)
		target=debian-mipsel
		;;
	linux-gnu-powerpc)
		target=linux-ppc
		;;
	linux-gnu-gnuspe-powerpc)
		target=linux-ppc
		;;
	linux-gnu-supersparc)
		target=linux-sparcv8
		;;
	linux-gnu-sparc)
		target=linux-sparcv8
		;;
	darwin-i386)
		target=darwin-i386-cc
		;;
	esac
	# inject machine-specific flags
	sed -i -e "s|^\(\"$target\",\s*\"[^:]\+\):\([^:]\+\)|\1:${CFLAG}|g" Configure
        useprefix=${prefix}
        if [ -z "$useprefix" ]; then
                useprefix=/
        fi        
	perl ./Configure shared --prefix=$useprefix --openssldir=${libdir}/ssl $target
}

do_compile () {
	oe_runmake
}

do_install () {
	oe_runmake INSTALL_PREFIX="${D}" MANDIR="${mandir}" install

	# On x86_64, move lib/* to lib64
	if [ "${libdir}" != "${prefix}/lib" ]
	then
		install -d ${D}${libdir} ${D}${libdir}/pkgconfig
		mv ${D}${prefix}/lib/lib* ${D}${libdir}
		mv ${D}${prefix}/lib/pkgconfig/*.pc ${D}${libdir}/pkgconfig
	fi

	install -d ${D}${includedir}
	cp --dereference -R include/openssl ${D}${includedir}
}

PACKAGES =+ "${PN}-misc ${PN}-engines"
FILES_${PN}-misc = "${libdir}/ssl/misc ${libdir}/ssl/openssl.cnf"
FILES_${PN}-engines = "${libdir}/ssl/engines/*.so"
FILES_${PN}-dbg =+ "${libdir}/ssl/engines/.debug"
FILES_${PN}-doc =+ "${libdir}/ssl/man"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "crypto ssl"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
DEPENDS_${PN}-dev = ""
RDEPENDS_${PN}-libcrypto = "libc libgcc libdl"
RDEPENDS_${PN}-libssl = "libc libdl libcrypto"
