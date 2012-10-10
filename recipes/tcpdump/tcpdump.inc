# -*- mode:python; -*-
DESCRIPTION = "A sophisticated network protocol analyzer"
HOMEPAGE = "http://www.tcpdump.org/"
LICENSE = "BSD-4-Clause*"

RECIPE_TYPES = "machine"

inherit autotools

SRC_URI = "http://www.tcpdump.org/release/tcpdump-${PV}.tar.gz \
	file://tcpdump_configure_no_-O2.patch \
	file://0001-minimal-IEEE802.15.4-allowed.patch \
	file://ipv6-cross.patch \
	file://configure.patch \
"

DEPENDS = "libpcap"
RDEPENDS_${PN} = "libpcap"

RECIPE_FLAGS += "tcpdump_ipv6"
EXTRA_OECONF_IPV6 = " --disable-ipv6"
EXTRA_OECONF_IPV6:>USE_tcpdump_ipv6 = " --enable-ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"

RECIPE_FLAGS += "tcpdump_smb"
EXTRA_OECONF_SMB = "--disable-smb"
EXTRA_OECONF_SMB:USE_tcpdump_smb = "--enable-smb"
EXTRA_OECONF += "${EXTRA_OECONF_SMB}"

RECIPE_FLAGS += "tcpdump_crypto"
EXTRA_OECONF_CRYPTO = "--without-crypto"
EXTRA_OECONF_CRYPTO:USE_tcpdump_crypto = "--with-crypto=${STAGE_DIR}/${HOST_TYPE}${prefix}"
EXTRA_OECONF += "${EXTRA_OECONF_CRYPTO}"
DEPENDS_CRYPTO = ""
DEPENDS_CRYPTO:USE_tcpdump_crypto = "libcrypto"
DEPENDS += "${DEPENDS_CRYPTO}"
DEPENDS_${PN} += "${DEPENDS_CRYPTO}"

RECIPE_FLAGS += "tcpdump_smi"
EXTRA_OECONF_SMI = "--without-smi"
EXTRA_OECONF_SMI:USE_tcpdump_smi = "--with-smi"
EXTRA_OECONF += "${EXTRA_OECONF_SMI}"
DEPENDS_SMI = ""
DEPENDS_SMI:USE_tcpdump_smi = "libsmi"
DEPENDS += "${DEPENDS_SMI}"
DEPENDS_${PN} += "${DEPENDS_SMI}"

do_install[postfuncs] += "do_install_extra"
do_install_extra () {
	# tcpdump 4.0.0 installs a copy to /usr/sbin/tcpdump.4.0.0
	rm -f ${D}${sbindir}/tcpdump.${PV}
}
