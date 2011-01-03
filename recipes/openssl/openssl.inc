DESCRIPTION = "Secure Socket Layer (SSL) binary and related cryptographic tools."
HOMEPAGE = "http://www.openssl.org/"
LICENSE = "openssl"
SECTION = "libs/network"
DEPENDS = "${HOST_ARCH}/sysroot-libdl"
SRC_URI = "http://www.openssl.org/source/openssl-${PV}.tar.gz"

BBCLASSEXTEND = "sdk"

AR_append = " r"
CFLAG = "${@base_conditional('TARGET_ENDIAN', 'le', '-DL_ENDIAN', '-DB_ENDIAN', d)} \
	-DTERMIO ${TARGET_CFLAGS}"

PARALLEL_MAKE = ""

export OE_LDFLAGS="${LDFLAGS}"

export DIRS = "crypto ssl apps engines"
export EX_LIBS = "-lgcc -ldl"
export AS = "${CC} -c"

PACKAGES =+ "${PN}-libcrypto ${PN}-libssl ${PN}-misc ${PN}-engines"

FILES_${PN}-libcrypto = "${libdir}/libcrypto${SOLIBS}"
FILES_${PN}-libssl = "${libdir}/libssl${SOLIBS}"
FILES_${PN}-misc = "${libdir}/ssl/misc ${libdir}/ssl/openssl.cnf"
FILES_${PN}-engines = "${libdir}/ssl/engines/${SOLIBS}"
FILES_${PN}-dev =+ "${libdir}/engines/lib*${SOLIBSDEV}"
FILES_${PN}-dbg =+ "${libdir}/engines/.debug"
FILES_${PN}-doc =+ "${libdir}/ssl/man"

PROVIDES_${PN}-libcrypto = "libcrypto${RE}"
PROVIDES_${PN}-libssl = "libssl${RE}"

RPROVIDES_${PN}-libcrypto = "libcrypto${RE}"
RPROVIDES_${PN}-libssl = "libssl${RE}"

do_configure_prepend_darwin () {
	sed -i -e '/version-script=openssl\.ld/d' Configure
}

do_configure () {
	cd util
	perl perlpath.pl ${bindir}
	cd ..
	ln -sf apps/openssl.pod crypto/crypto.pod ssl/ssl.pod doc/

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
        if [ "x$useprefix" == "x" ]; then
                useprefix=/
        fi        
	perl ./Configure shared --prefix=$useprefix --openssldir=${libdir}/ssl $target
}

do_compile () {
	oe_runmake
}

do_install () {
	oe_runmake INSTALL_PREFIX="${D}" install

	# On x86_64, move lib/* to lib64
	if [ "${libdir}" != "${prefix}/lib" ]
	then
		install -d ${D}${libdir} ${D}${libdir}/pkgconfig
		mv ${D}${prefix}/lib/lib* ${D}${libdir}
		mv ${D}${prefix}/lib/pkgconfig/*.pc ${D}${libdir}/pkgconfig
	fi

	oe_libinstall -so libcrypto ${D}${libdir}
	oe_libinstall -so libssl ${D}${libdir}

	install -d ${D}${includedir}
	cp --dereference -R include/openssl ${D}${includedir}
}
