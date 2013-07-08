inherit autotools library 

include conf/fetch/sourceforge.conf

DEPENDS = "libpthread"
DEPENDS_${PN} = "${DEPENDS}"

SRC_URI ="${SOURCEFORGE_MIRROR}/pupnp/${PN}-${PV}.tar.bz2"