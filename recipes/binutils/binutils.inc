# -*- mode:python; -*-
SUMMARY = "A GNU collection of binary utilities"
DESCRIPTION = "The GNU Binutils are a collection of binary tools. \
The main ones are ld (GNU Linker), and as (GNU Assembler). This \
package also includes addition tools such as addr2line (Converts \
addresses into filenames and line numbers), ar (utility for creating, \
modifying and extracting archives), nm (list symbols in object \
files), objcopy (copy and translate object files), objdump (Display \
object information), and other tools and related libraries."
HOMEPAGE = "http://www.gnu.org/software/binutils/"
BUGTRACKER = "http://sourceware.org/bugzilla/"

inherit autotools gettext

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/binutils/binutils-${PV}.tar.bz2 "

DEPENDS = "native:flex native:bison"

EXTRA_OECONF = "--enable-install-libbfd --enable-shared"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "bfd opcodes"
BINUTILS_VERSION ?= "${PV}"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib::-${BINUTILS_VERSION}.so:.so"

PROVIDES_${PN}-dev = "libiberty"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
    addr2line as c++filt gprof ld nm objcopy objdump ranlib readelf elfedit \
    size strip ar strings embedspu"

do_install[postfuncs] += "do_install_hardlinkfixup"
do_install_hardlinkfixup () {
	# FIXME: this properly does not work for cross, sdk-cross and
	# canadian-cross ...
	cd ${D}${prefix}/${TARGET_ARCH}/bin
	for bin in *; do
		rm $bin
		ln -s ../../..${bindir}/$bin
	done
	cd ${D}${bindir}
	rm ld
	ln -s ld.bfd ld
}

FILES_${PN}-dbg += "${prefix}/${TARGET_ARCH}/bin/.debug"

FILES_${PN}-ld = "${bindir}/ld.bfd"
FILES_${PN}-ar += "${prefix}/${TARGET_ARCH}/bin/ar"
FILES_${PN}-as += "${prefix}/${TARGET_ARCH}/bin/as"
FILES_${PN}-ld += "${bindir}/ld.bfd ${prefix}/${TARGET_ARCH}/bin/ld ${prefix}/${TARGET_ARCH}/bin/ld.bfd"
FILES_${PN}-nm += "${prefix}/${TARGET_ARCH}/bin/nm"
FILES_${PN}-objcopy += "${prefix}/${TARGET_ARCH}/bin/objcopy"
FILES_${PN}-objdump += "${prefix}/${TARGET_ARCH}/bin/objdump"
FILES_${PN}-ranlib += "${prefix}/${TARGET_ARCH}/bin/ranlib"
FILES_${PN}-strip += "${prefix}/${TARGET_ARCH}/bin/strip"

PACKAGES += "${PN}-ldscripts"
FILES_${PN}-ldscripts = "${prefix}/${TARGET_ARCH}/lib/ldscripts"

RDEPENDS_${PN}-addr2line = "binutils-libbfd"
RDEPENDS_${PN}-as = "libbfd libopcodes"
RDEPENDS_${PN}-c++filt = "libbfd"
RDEPENDS_${PN}-gprof = "libbfd"
RDEPENDS_${PN}-ld = "libbfd"
RDEPENDS_${PN}-nm = "libbfd"
RDEPENDS_${PN}-objcopy = "libbfd"
RDEPENDS_${PN}-objdump = "libbfd libopcodes"
RDEPENDS_${PN}-libopcodes = "binutils-libbfd"
RDEPENDS_${PN}-ranlib = "libbfd"
RDEPENDS_${PN}-readelf = "libbfd"
RDEPENDS_${PN}-elfedit = "libbfd"
RDEPENDS_${PN}-size = "libbfd"
RDEPENDS_${PN}-strip = "libbfd"
RDEPENDS_${PN}-ar = "libbfd"
RDEPENDS_${PN}-strings = "libbfd"

# The binutils package is used to pull in all provided util features
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PROVIDES}"
