SUMMARY = "TCP / IP networking and traffic control utilities"
DESCRIPTION = "Iproute2 is a collection of utilities for controlling \
TCP / IP networking and traffic control in Linux.  Of the utilities ip \
and tc are the most important.  ip controls IPv4 and IPv6 \
configuration and tc stands for traffic control."
LICENSE = "GPLv2+"

inherit autotools-autoreconf pkgconfig auto-package-utils

SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/shemminger/iproute2.git;commit=${GIT_COMMIT}"
S = "${SRCDIR}/iproute2"

DEPENDS += "libdl libresolv libm libdb4 libnl-dev"

do_compile[prefuncs] += "do_compile_add_libnl"
do_compile_add_libnl () {
	sed -i -e 's#^\(CFLAGS.*\)#\1 -I\${STAGE_DIR}\/\${HOST_TYPE}\/usr\/include\/libnl3\/#' Makefile
}

EXTRA_OEMAKE = "CC='${CC}' DESTDIR=${S} LIBDIR=${libdir} SBINDIR=${base_sbindir} CONFDIR=${sysconfdir}/iproute2 DOCDIR=${docdir}/iproute2 MANDIR=${mandir} ARPDDIR=${localstatedir}/lib/arpd SUBDIRS='lib tc ip' SBINDIR=${base_sbindir}"

FILES_${PN} += "${base_libdir}/tc/*"
FILES_${PN}-dbg += "${base_libdir}/tc/.debug"

AUTO_PACKAGE_UTILS = "ifcfg ip routef routel rtmon rtpr tc"
RDEPENDS_${PN}-ip += "libresolv libc libm libdl"
RDEPENDS_${PN}-rtmon += "libresolv libc libm libdl"
RDEPENDS_${PN}-tc += "libresolv libc libm libdl"
