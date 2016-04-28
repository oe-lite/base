inherit autotools library 

COMPATIBLE_HOST_ARCHS = ".*linux"

include conf/fetch/sourceforge.conf

#Only used for Aarch64
AUTOCONFDIRS = "/config.aux"

DEPENDS = "libpthread"
DEPENDS_${PN} = "${DEPENDS}"

SRC_URI ="${SOURCEFORGE_MIRROR}/pupnp/${PN}-${PV}.tar.bz2"
