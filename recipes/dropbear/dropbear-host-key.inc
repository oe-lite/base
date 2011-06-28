DESCRIPTION = "Pregenerated dropbear rsa host key"
RDEPENDS_${PN} = "dropbear"

SRC_URI = "file://dropbear_rsa_host_key"

do_install() {
	install -d ${D}${sysconfdir}/dropbear
	install -m 0600 ${SRCDIR}/dropbear_rsa_host_key \
		${D}${sysconfdir}/dropbear/
}

