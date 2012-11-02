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

	case "${HOST_OS}" in

	linux*)
		case "${HOST_CPU}" in
		i?86)		target="linux-elf" ;;
		armeb)		target="linux-generic32" ;;
		arm)		target="linux-armv4" ;;
		powerpc64)	target="linux-ppc64" ;;
		powerpc)	target="linux-ppc" ;;
		*)		target="linux-${HOST_CPU}" ;;
		esac
		;;

	mingw*)
		case "${HOST_CPU}" in
		i?86)		target="mingw" ;;
		x86_64)		target="mingw64" ;;
		*)		target="mingw-${HOST_CPU}" ;;
		esac
		;;

	darwin*)
		case "${HOST_CPU}" in
		i?86)		target="darwin-i386-cc" ;;
		x86_64)		target="darwin64-x86_64-cc" ;;
		powerpc)	target="darwin-ppc-cc" ;;
		*)		target="darwin-${HOST_CPU}" ;;
		esac
		;;

	*)
		target="${HOST_OS}-${HOST_CPU}"
		;;

	esac

	# inject machine-specific flags
	sed -i -e "s|^\(\"$target\",\s*\"[^:]\+\):\([^:]\+\)|\1:${CFLAG}|g" Configure
	useprefix=${prefix}
	if [ -z "$useprefix" ]; then
		useprefix=/
	fi
        uselibdir=`echo ${libdir} | sed -e "s%^$useprefix%%"`
	perl ./Configure shared \
		--prefix=$useprefix \
		--libdir=$uselibdir \
		--openssldir=${libdir}/ssl \
		$target
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
