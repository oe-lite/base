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

inherit autotools gettext auto-package-utils

DEPENDS = "flex-native bison-native"

AUTO_PACKAGE_UTILS = " \
	addr2line as c++filt gprof ld nm objcopy \
	objdump ranlib readelf size strip"

EXTRA_OECONF = "--enable-install-libbfd --enable-shared"
