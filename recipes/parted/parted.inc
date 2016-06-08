SUMMARY = "A tool for manipulating partition tables"
DESCRIPTION = "GNU Parted manipulates partition tables. This is useful for \
 creating space for new operating systems, reorganizing disk usage, copying \
 data on hard disks and disk imaging."

LICENSE = "GPL-3.0+"
HOMEPAGE = "http://www.gnu.org/software/parted/"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/parted/parted-${PV}.tar.xz \
	file://compile-failure-while-dis.patch"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools

EXTRA_OECONF += "--disable-device-mapper"

DEPENDS += "libdl libuuid libtermcap libreadline"
RDEPENDS += "libdl libuuid libtermcap libreadline"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "parted-fs-resize parted"

DEPENDS_${PN} += "libc libdl libncurses libparted libreadline libuuid"
RDEPENDS_${PN} += "libc libdl libncurses libparted libreadline libuuid"

DEPENDS_${PN}-libparted-fs-resize += "libc"
RDEPENDS_${PN}-libparted-fs-resize += "libc"
PROVIDES_${PN}-libparted-fs-resize += "libparted-fs-resize-0"

DEPENDS_${PN}-libparted += "libc libdl libuuid"
RDEPENDS_${PN}-libparted += "libc libdl libuuid"
PROVIDES_${PN}-libparted += "libparted-2"
