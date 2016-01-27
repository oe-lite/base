DESCRIPTION = "A daemon which implements the Point-to-Point Protocol for dial-up networking"
HOMEPAGE = "http://www.samba.org/ppp/"

SRC_URI = "https://download.samba.org/pub/ppp/ppp-${PV}.tar.gz \
           file://makefile.patch \
           file://cifdefroute.patch \
           file://pppd-resolv-varrun.patch \
           file://makefile-remove-hard-usr-reference.patch \
           file://pon \
           file://poff \
           file://init \
           file://ip-up \
           file://ip-down \
           file://08setupdns \
           file://92removedns \
           file://copts.patch \
           file://pap \
           file://ppp_on_boot \
           file://provider \
           file://0001-ppp-Fix-compilation-errors-in-Makefile.patch \
           file://fix-CVE-2015-3310.patch \
           "
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools

DEPENDS = "libdl libcrypt libutil libpcap libresolv"

EXTRA_OEMAKE = "STRIPPROG=${STRIP} MANDIR=${D}${datadir}/man/man8 INCDIR=${D}${includedir} LIBDIR=${D}${libdir}/pppd/${PV} BINDIR=${D}${sbindir}"
EXTRA_OEMAKE += ' COPTS="${CFLAGS} -I${S}/include" '
EXTRA_OECONF = "--disable-strip"

do_install[postfuncs] += "do_install_extra"
do_install_extra () {
	mkdir -p ${D}${bindir}/ ${D}${sysconfdir}/init.d
	mkdir -p ${D}${sysconfdir}/ppp/ip-up.d/
	mkdir -p ${D}${sysconfdir}/ppp/ip-down.d/
	install -m 0755 ${SRCDIR}/pon ${D}${bindir}/pon
	install -m 0755 ${SRCDIR}/poff ${D}${bindir}/poff
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/ppp
	install -m 0755 ${SRCDIR}/ip-up ${D}${sysconfdir}/ppp/
	install -m 0755 ${SRCDIR}/ip-down ${D}${sysconfdir}/ppp/
	install -m 0755 ${SRCDIR}/08setupdns ${D}${sysconfdir}/ppp/ip-up.d/
	install -m 0755 ${SRCDIR}/92removedns ${D}${sysconfdir}/ppp/ip-down.d/
	mkdir -p ${D}${sysconfdir}/chatscripts
	mkdir -p ${D}${sysconfdir}/ppp/peers
	install -m 0755 ${SRCDIR}/pap ${D}${sysconfdir}/chatscripts
	install -m 0755 ${SRCDIR}/ppp_on_boot ${D}${sysconfdir}/ppp/ppp_on_boot
	install -m 0755 ${SRCDIR}/provider ${D}${sysconfdir}/ppp/peers/provider
}

PACKAGES =+ "${PN}-oa ${PN}-oe ${PN}-radius ${PN}-winbind ${PN}-minconn ${PN}-password ${PN}-l2tp ${PN}-tools"
FILES_${PN} += "${libdir}/pppd/${PV}/*.so"
DEPENDS_${PN} = "libc libcrypt libdl libpcap libutil"
RDEPENDS_${PN} = "libc libcrypt libdl libpcap libutil"
FILES_${PN}-oa = "${libdir}/pppd/${PV}/pppoatm.so"
FILES_${PN}-oe = "${sbindir}/pppoe-discovery ${libdir}/pppd/${PV}/rp-pppoe.so"
DEPENDS_${PN}-oe = "libc"
RDEPENDS_${PN}-oe = "libc"
FILES_${PN}-radius = "${libdir}/pppd/${PV}/radius.so ${libdir}/pppd/${PV}/radattr.so ${libdir}/pppd/${PV}/radrealms.so"
FILES_${PN}-winbind = "${libdir}/pppd/${PV}/winbind.so"
FILES_${PN}-minconn = "${libdir}/pppd/${PV}/minconn.so"
FILES_${PN}-password = "${libdir}/pppd/${PV}/pass*.so"
FILES_${PN}-l2tp = "${libdir}/pppd/${PV}/*l2tp.so"
FILES_${PN}-tools = "${sbindir}/pppstats ${sbindir}/pppdump"
DEPENDS_${PN}-tools = "libc"
RDEPENDS_${PN}-tools = "libc"
FILES_${PN}-dbg = "${libdir}/pppd/${PV}/.debug/*.so \
                   ${sbindir}/.debug/*"
