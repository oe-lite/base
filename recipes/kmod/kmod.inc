DESCRIPTION = "kmod - Linux kernel module handling"
LICENSE = "LGPL-2.1+ GPL-2.0+"
RECIPE_TYPES = "native machine"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools auto-package-utils auto-package-libs

SRC_URI = "https://www.kernel.org/pub/linux/utils/kernel/kmod/kmod-${PV}.tar.xz"

AUTO_PACKAGE_UTILS = "depmod insmod lsmod modinfo modprobe rmmod"
AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}_${PV}"
AUTO_PACKAGE_UTILS_DEPENDS = "${PN}_${PV}"

FILES_${PN} = "${base_bindir}/${PN}"
DEPENDS_${PN} = "libc"
RDEPENDS_${PN} = "libc"
EXTRA_OECONF = "--disable-manpages --bindir=${base_bindir}"
EXTRA_OECONF += "--with-bashcompletiondir=${datadir}/bash-completion/completions"

AUTO_PACKAGE_LIBS = "kmod"
AUTO_PACKAGE_LIBS_DEPENDS = "libc"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc"
LIBRARY_VERSION_${PN}-libkmod = "2"

PACKAGES += "${PN}-completions"
FILES_${PN}-completions = "${datadir}/bash-completion"

do_install[postfuncs] = "do_install_symlinks"
do_install_symlinks() {
    install -d -m 0755 ${D}${base_sbindir}
    for util in depmod insmod lsmod modinfo modprobe rmmod; do
        ln -s ..${base_bindir}/kmod ${D}/${base_sbindir}/$util
    done
}
