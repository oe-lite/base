DESCRIPTION = "ISC Internet Domain Name Server"
HOMEPAGE = "http://www.isc.org/sw/bind/"
SECTION = "console/network"

LICENSE = "ISC"
LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=fe11ac92dcbd84134d91b6e2c2eccab5"

DEPENDS = "openssl-dev \
           ${TARGET_ARCH}/sysroot-libdl"

SRC_URI = "ftp://ftp.isc.org/isc/bind9/${PV}/${PN}-${PV}.tar.gz \
	       file://conf.patch \
           file://cross-build-fix.patch"


# --enable-exportlib is necessary for building dhcp
EXTRA_OECONF = " --enable-ipv6=no --with-randomdev=/dev/random --disable-threads \
                 --disable-devpoll --disable-epoll \
                 --sysconfdir=${sysconfdir}/bind \
                 --with-openssl=${STAGE_DIR}/sysroot/usr --with-libxml2=${STAGE_DIR}/sysroot/usr \
                 --enable-exportlib --with-export-includedir=${includedir} --with-export-libdir=${libdir} \
               "
inherit autotools sysvinit
RECIPE_OPTIONS += "bind_sysvinit_start bind_sysvinit_stop"
SYSVINI_SCRIPT_bind = "bind"
DEFAULT_CONFIG_bind_sysvinit_start= "25"
DEFAULT_CONFIG_bind_sysvinit_stop = "20"

PARALLEL_MAKE = ""

PACKAGES_prepend = "${PN}-utils "
FILES_${PN}-utils = "${bindir}/host ${bindir}/dig ${bindir}/nslookup"
FILES_${PN}-dev += "${bindir}/isc-config.h"

do_install_append() {
	rm "${D}/usr/bin/nslookup"
	install -d "${D}/etc/bind"
	install -d "${D}/etc/init.d"
	install -m 644 ${S}/conf/* "${D}/etc/bind"
	install -m 755 "${S}/init.d" "${D}/etc/init.d/bind"
}

CONFFILES_${PN} = " \
	${sysconfdir}/bind/named.conf \
	${sysconfdir}/bind/named.conf.local \
	${sysconfdir}/bind/named.conf.options \
	${sysconfdir}/bind/db.0 \
	${sysconfdir}/bind/db.127 \
	${sysconfdir}/bind/db.empty \
	${sysconfdir}/bind/db.local \
	${sysconfdir}/bind/db.root \
	"

