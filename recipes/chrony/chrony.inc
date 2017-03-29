SUMMARY = "Versatile implementation of the Network Time Protocol"
HOMEPAGE = "http://chrony.tuxfamily.org/"
LICENSE = "GPL-2.0"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine native"

SRC_URI = "https://download.tuxfamily.org/chrony/chrony-${PV}.tar.gz"

inherit make
inherit auto-package-utils

DEPENDS += "libc libm"

DEP_READLINE = ""
DEP_READLINE:USE_chrony_readline = "libreadline libncurses"
CONF_READLINE = "--without-readline"
CONF_READLINE:USE_chrony_readline = ""
RECIPE_FLAGS += "chrony_readline"
DEFAULT_USE_chrony_readline = True
DEPENDS += "${DEP_READLINE}"

do_configure() {
    ./configure --sysconfdir=${sysconfdir} \
                --bindir=${bindir} \
                --sbindir=${sbindir} \
                --localstatedir=${localstatedir} \
                --datarootdir=${datadir} \
                --host-system=Linux \
                --host-machine=${HOST_CPU} \
                ${CONF_READLINE} --without-editline
}

AUTO_PACKAGE_UTILS = "chronyc chronyd"
AUTO_PACKAGE_UTILS_DEPENDS += "libc libm"
AUTO_PACKAGE_UTILS_RDEPENDS += "libc libm"

RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"

DEPENDS_${PN}-chronyc += "${DEP_READLINE}"
RDEPENDS_${PN}-chronyc += "${DEP_READLINE}"

SRC_URI += "file://chrony.conf"
PACKAGES =+ "${PN}-conf"
FILES_${PN}-conf = "${sysconfdir}"
do_install_conf() {
    install -d ${D}${sysconfdir}
    install -m 0644 ${SRCDIR}/chrony.conf ${D}${sysconfdir}
    sed -i -e 's!@localstatedir@!${localstatedir}!' ${D}${sysconfdir}/chrony.conf
}
do_install[postfuncs] += "do_install_conf"
RDEPENDS_${PN}-chronyd += "${PN}-conf"
