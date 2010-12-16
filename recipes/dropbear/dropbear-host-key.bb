DESCRIPTION = "Pregenerated dropbear rsa host key"
SECTION = "console/network"
RDEPENDS_${PN} = "dropbear"

SRC_URI = "file://dropbear_rsa_host_key"

do_install() {
	install -d ${D}${sysconfdir}/dropbear
	install -m 0600 ${WORKDIR}/dropbear_rsa_host_key \
		${D}${sysconfdir}/dropbear/
}

