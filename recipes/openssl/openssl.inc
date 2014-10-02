# -*- mode:python; -*-
DESCRIPTION = "Secure Socket Layer (SSL) binary and related \
	cryptographic tools."
HOMEPAGE = "http://www.openssl.org/"
LICENSE = "openssl"

RECIPE_TYPES = "machine native sdk"

#Remove last letter from openssl minor version
FILESPATHPKG = "${PN}-${@'${PV}'[:-1]}:openssl"

inherit c make pkgconfig

SRC_URI = "http://www.openssl.org/source/openssl-${PV}.tar.gz"

DEPENDS = "${DEPENDS_HOST_OS} libc libgcc"
DEPENDS_HOST_OS = "libdl"
DEPENDS_HOST_OS:HOST_OS_mingw32 = ""

CFLAG = "${@['-DL_ENDIAN', '-DB_ENDIAN']['${HOST_ENDIAN}'=='b']} ${HOST_CFLAGS}"
CFLAG:>HOST_KERNEL_linux = " -DTERMIO"

CROSS:native = ""
export WINDRES = "${CROSS}windres"
export DIRS = "crypto ssl apps engines"
export EX_LIBS = "-lgcc -ldl"
export AS = "${CC} -c"

do_configure () {
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

	# As the openssl buildsystem assumes that bin, include and libdirs
	# all are subdirs to same prefix, we need to force prefix to ""
	# to be able to handle cases where fx. prefix=/usr and bindir=/bin
	# and instead manually patch in those subdirs with full path.
	sedc=""
	if [ "${bindir}" != "/bin" ] ; then
		sedc=$sedc"s%\(\$(INSTALLTOP)\)/bin%\1${bindir}%g;"
	fi
	if [ "${includedir}" != "/include" ] ; then
		sedc=$sedc"s%\(\$(INSTALLTOP)\)/include%\1${includedir}%g;"
	fi
	if [ -n "$sedc" ] ; then
		find . -name Makefile -exec sed -i -e "$sedc" {} \;
		sed -i -e "$sedc" Makefile.org
        fi

	perl ./Configure shared \
		--prefix=/ \
		--libdir=${libdir} \
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

DEPENDS_${PN} += " ${PN}-libcrypto ${PN}-libssl"
RDEPENDS_${PN} += " ${PN}-libcrypto ${PN}-libssl ${PN}-engines ${PN}-misc"

PACKAGES =+ "${PN}-misc ${PN}-engines"
FILES_${PN}-misc = "${libdir}/ssl/misc ${libdir}/ssl/openssl.cnf"
FILES_${PN}-engines = "${libdir}/ssl/engines/*.so"
FILES_${PN}-engines:HOST_OS_mingw32 = "${libdir}/ssl/engines/*.dll"
FILES_${PN}-engines:HOST_KERNEL_darwin = "${libdir}/ssl/engines/*.dylib"
FILES_${PN}-dbg =+ "${libdir}/ssl/engines/.debug"
FILES_${PN}-doc =+ "${libdir}/ssl/man"

SRC_URI += "file://engines-install-in-libdir-ssl.patch"
SRC_URI += "file://mingw.patch"
SRC_URI += "file://fix-pod-errors.patch"
SRC_URI += "file://oe-ldflags.patch file://shared-libs.patch"
SRC_URI += "file://no-librpath-rpath.patch"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "crypto ssl"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
inherit auto-package-utils
AUTO_PACKAGE_UTILS = "openssl c_rehash"
DEPENDS_${PN}-openssl += "libc libdl libcrypto libssl"
RDEPENDS_${PN}-openssl += "libc libdl libcrypto libssl"
DEPENDS_${PN}-dev = ""
FILES_${PN}-libcrypto += " ${LIBCRYPTO_FILES}"  
LIBCRYPTO_FILES = ""
LIBCRYPTO_FILES:HOST_OS_mingw32 = "${sharedlibdir}/libeay32.dll"
FILES_${PN}-libssl += " ${LIBSSL_FILES}"
LIBSSL_FILES = ""
LIBSSL_FILES:HOST_OS_mingw32 = "${sharedlibdir}/ssleay32.dll"
DEPENDS_${PN}-libcrypto += " ${DEPENDS}"
DEPENDS_${PN}-libssl += " ${DEPENDS} libcrypto"
RDEPENDS_${PN}-libcrypto += "libc libgcc ${DEPENDS_HOST_OS}"
RDEPENDS_${PN}-libssl += "${DEPENDS_HOST_OS} libcrypto"
