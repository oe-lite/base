DESCRIPTION = "Bonjour, also known as zero-configuration networking, enables automatic discovery of computers, devices, and services on IP networks."
HOMEPAGE = "http://developer.apple.com/networking/bonjour/"

RECIPE_TYPES = "machine"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make sysvinit

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "dns_sd nss_mdns"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "mdnsd"

SRC_URI = "http://opensource.apple.com/tarballs/mDNSResponder/mDNSResponder-${PV}.tar.gz \
           file://build.patch \
	   file://mDNS \
"
DEPENDS_${PN}-mdnsd += "libc"
RDEPENDS_${PN}-mdnsd += "libc"

RECIPE_FLAGS += "mdns_sysvinit_start mdns_sysvinit_stop"
SYSVINIT_SCRIPT_mdns = "mDNS"
DEFAULT_USE_mdns_sysvinit_start = "26"
DEFAULT_USE_mdns_sysvinit_stop = "26"

do_install[postfuncs] =+ "do_install_extra_files"
do_install_extra_files() {
        sysvinit_install_script ${SRCDIR}/mDNS mDNS
}

PARALLEL_MAKE = ""

S = "${SRCDIR}/mDNSResponder-${PV}"

EXTRA_OEMAKE = "CC='${CC}' LD='${LD}'"

do_compile() {
    cd mDNSPosix
    oe_runmake os=linux DEBUG=0
}

do_install () {
    install -d ${D}${sbindir}
    install -m 0755 mDNSPosix/build/prod/mdnsd ${D}${sbindir}

    install -d ${D}${libdir}
    install -m 0644  mDNSPosix/build/prod/libdns_sd.so ${D}${libdir}/libdns_sd.so.1
    ln -s libdns_sd.so.1 ${D}${libdir}/libdns_sd.so

    install -d ${D}${includedir}
    install -m 0644 mDNSShared/dns_sd.h ${D}${includedir}

    install -d ${D}${mandir}/man8
    install -m 0644 mDNSShared/mDNSResponder.8 ${D}${mandir}/man8/mdnsd.8


    install -d ${D}${libdir}
    install -m 0644 mDNSPosix/build/prod/libnss_mdns-0.2.so ${D}${libdir}/libnss_mdns-0.2.so
    ln -s libnss_mdns-0.2.so ${D}${libdir}/libnss_mdns.so.2

    install -d ${D}${sysconfdir}
    install -m 0644 mDNSPosix/nss_mdns.conf ${D}${sysconfdir}

    install -d ${D}${mandir}/man5
    install -m 0644 mDNSPosix/nss_mdns.conf.5 ${D}${mandir}/man5

    install -d ${D}${mandir}/man8
    install -m 0644 mDNSPosix/libnss_mdns.8 ${D}${mandir}/man8
}

pkg_postinst_${PN} () {
    sed -e '/^hosts:/s/\s*\<mdns\>//' \
        -e 's/\(^hosts:.*\)\(\<files\>\)\(.*\)\(\<dns\>\)\(.*\)/\1\2 mdns\3\4\5/' \
        -i $D/etc/nsswitch.conf
}

pkg_prerm_${PN} () {
    sed -e '/^hosts:/s/\s*\<mdns\>//' \
        -e '/^hosts:/s/\s*mdns//' \
        -i $D/etc/nsswitch.conf
}

# The .so and .so.1 files do not contain version information (e.g. libtool not
# used). This confuses packages rdepend and linked with this lib if the .so
# file is not there.
FILES_${PN}-libnss-mdns += "${libdir}/libnss_mdns-0.2.so ${sysconfdir}/nss_mdns.conf"
FILES_${PN}-libdns-sd-dev = "${includedir}/dns_sd.h"
FILES_${PN}-libdns-sd += "${libdir}/libdns_sd.so"
RDEPENDS_${PN} += "${PN}-mdnsd ${PN}-libdns-sd"
