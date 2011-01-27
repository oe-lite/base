DESCRIPTION = "ISC Internet Domain Name Server"
HOMEPAGE = "http://www.isc.org/sw/bind/"
LICENSE = "ISC"

inherit autotools sysvinit

DEPENDS = "openssl-dev ${TARGET_ARCH}/sysroot-libdl"

SRC_URI = "ftp://ftp.isc.org/isc/bind9/${PV}/${PN}-${PV}.tar.gz"

# --enable-exportlib is necessary for building dhcp
EXTRA_OECONF = "\
    --enable-ipv6=no \
    --with-randomdev=/dev/random \
    --disable-threads \
    --disable-devpoll --disable-epoll \
    --sysconfdir=${sysconfdir}/bind \
    --with-openssl=${TARGET_SYSROOT}${target_prefix} \
    --with-libxml2=${TARGET_SYSROOT}${target_prefix} \
    --enable-exportlib \
    --with-export-includedir=${includedir} \
    --with-export-libdir=${libdir} \
"

RECIPE_OPTIONS += "bind_sysvinit_start bind_sysvinit_stop"
SYSVINI_SCRIPT_bind = "bind"
DEFAULT_CONFIG_bind_sysvinit_start= "20"
DEFAULT_CONFIG_bind_sysvinit_stop = "20"

# last verified with bind-9.7.2-P3
PARALLEL_MAKE = ""

do_install_append() {
	rm "${D}/usr/bin/nslookup"
	install -d "${D}/etc/bind"
	install -d "${D}/etc/init.d"
	install -m 644 ${S}/conf/* "${D}/etc/bind"
	install -m 755 "${S}/init.d" "${D}/etc/init.d/bind"
}

FILES_${PN}-dev += "${bindir}/isc-config.h"

PACKAGES_prepend = "${PN}-utils "
FILES_${PN}-utils = "${bindir}/host ${bindir}/dig ${bindir}/nslookup"
