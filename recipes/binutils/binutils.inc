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
LICENSE = "GPLv3"

inherit autotools gettext

DEPENDS = "flex-native bison-native"

EXTRA_OECONF = "--enable-install-libbfd --enable-shared"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "bfd opcodes"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}"
AUTO_PACKAGE_LIBS_LIBDIR = "${libdir}:lib::-${PV}.so:.so"

PROVIDES_${PN}-dev = "libiberty"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "\
    addr2line as c++filt gprof ld nm objcopy objdump ranlib readelf elfedit \
    size strip ar strings embedspu"


EXTRA_FILES_${PN}-ld = "${bindir}/ld.bfd"

RDEPENDS_${PN}-addr2line = "libbfd"
RDEPENDS_${PN}-as = "libbfd libopcodes"
RDEPENDS_${PN}-c++filt = "libbfd"
RDEPENDS_${PN}-gprof = "libbfd"
RDEPENDS_${PN}-ld = "libbfd"
RDEPENDS_${PN}-nm = "libbfd"
RDEPENDS_${PN}-objcopy = "libbfd"
RDEPENDS_${PN}-objdump = "libbfd libopcodes"
RDEPENDS_${PN}-ranlib = "libbfd"
RDEPENDS_${PN}-readelf = "libbfd"
RDEPENDS_${PN}-elfedit = "libbfd"
RDEPENDS_${PN}-size = "libbfd"
RDEPENDS_${PN}-strip = "libbfd"
RDEPENDS_${PN}-ar = "libbfd"
RDEPENDS_${PN}-strings = "libbfd"

#force binutils to run depend on all
RDEPENDS_${PN} = ${AUTO_PACKAGE_ALL_UTILS}
