DESCRIPTION = "strongSwan is an OpenSource IPsec implementation for the \
Linux operating system."
HOMEPAGE = "http://www.strongswan.org"
LICENSE = "GPLv2"
DEPENDS = "libgmp-dev libcrypto libssl openssl-dev libdl libm libpthread \
	librt libgmp"

SRC_URI = "http://download.strongswan.org/strongswan-${PV}.tar.bz2"


EXTRA_OECONF = "--disable-curl --disable-soup --disable-ldap --enable-gmp \
	--disable-mysql --disable-sqlite --enable-openssl"

inherit autotools

FILES_${PN}-dev += "${libdir}/ipsec/*.a \
		    ${libdir}/ipsec/*.la \
		    ${libdir}/ipsec/plugins/*.a \
		    ${libdir}/ipsec/plugins/*.la"
FILES_${PN}-dbg += "${libdir}/ipsec/.debug ${libdir}/ipsec/plugins/.debug \
		${libexecdir}/ipsec/.debug"
FILES_${PN} += "${libdir}/ipsec"
DEPENDS_${PN} += "libc"
DEPENDS_${PN}[qa] += "allow-missing-lib-depends"
RDEPENDS_${PN} = "libgmp libcrypto libssl libdl libm libpthread librt"
RDEPENDS_${PN}[qa] += "allow-missing-lib-rdepends"
