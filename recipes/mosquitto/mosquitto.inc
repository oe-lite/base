DESCRIPTION = "Mosquitto is an open source implementation of a\
	    server for version 3.1 and 3.1.1 of the MQTT protocol"

HOMEPAGE = "http://mosquitto.org"
LICENSE = "EPL-1.0"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine"

SRC_URI = "https://github.com/eclipse/mosquitto/archive/v${PV}.tar.gz"

S = "${SRCDIR}/mosquitto-${PV}"

inherit c++ make auto-package-libs auto-package-utils

DEPENDS = "librt libssl libuuid"

AUTO_PACKAGE_UTILS = "\
  ${PN} \
  ${PN}_sub \
  ${PN}_pub \
  ${PN}_passwd \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc lib${PN} libuuid"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libm lib${PN} libuuid"

DEPENDS_${PN}-${PN}-passwd += "libcrypto"
RDEPENDS_${PN}-${PN}-passwd += "libcrypto"

AUTO_PACKAGE_LIBS = "${PN} ${PN}pp"
AUTO_PACKAGE_LIBS_DEPENDS = "libpthread librt libz libm openssl libuuid"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libcrypto libpthread librt libssl"

DEPENDS_${PN}-lib${PN}pp += "lib${PN} libstdc++"
RDEPENDS_${PN}-lib${PN}pp += "lib${PN} libc libgcc-s libm libstdc++"

EXTRA_OEMAKE = "\
  WITH_SRV=no \
  WITH_DOCS=no \
  prefix=${prefix} \
"
