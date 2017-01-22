DESCRIPTION = "Mosquitto is an open source implementation of a\
	    server for version 3.1 and 3.1.1 of the MQTT protocol"

HOMEPAGE = "http://mosquitto.org"
LICENSE = "EPL-1.0"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine"

SRC_URI = "https://github.com/eclipse/mosquitto/archive/v${PV}.tar.gz"

S = "${SRCDIR}/mosquitto-${PV}"

inherit c++ make auto-package-libs auto-package-utils

RECIPE_FLAGS = "mosquitto_uuid mosquitto_websockets"
DEFAULT_USE_mosquitto_uuid = True
DEFAULT_USE_mosquitto_websockets = False

DEPENDS = "librt libssl"
DEPENDS:>USE_mosquitto_uuid = " libuuid"
DEPENDS:>USE_mosquitto_websockets = " libwebsockets"

AUTO_PACKAGE_UTILS = "\
  ${PN} \
  ${PN}_sub \
  ${PN}_pub \
  ${PN}_passwd \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc lib${PN}"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libm lib${PN}"

AUTO_PACKAGE_UTILS_DEPENDS:>USE_mosquitto_uuid = " libuuid"
AUTO_PACKAGE_UTILS_DEPENDS:>USE_mosquitto_websockets = " libwebsockets"

DEPENDS_${PN}-${PN}-passwd += "libcrypto"
RDEPENDS_${PN}-${PN}-passwd += "libcrypto"

AUTO_PACKAGE_LIBS = "${PN} ${PN}pp"
AUTO_PACKAGE_LIBS_DEPENDS = "libpthread librt libz libm libssl"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libcrypto libpthread librt libssl"

AUTO_PACKAGE_LIBS_RDEPENDS:>USE_mosquitto_uuid = " libuuid"
AUTO_PACKAGE_LIBS_RDEPENDS:>USE_mosquitto_websockets = " libwebsockets"

DEPENDS_${PN}-lib${PN}pp += "lib${PN} libstdc++"
RDEPENDS_${PN}-lib${PN}pp += "lib${PN} libc libgcc-s libm libstdc++"

EXTRA_OEMAKE_UUID = "WITH_UUID=no"
EXTRA_OEMAKE_UUID:USE_mosquitto_uuid = "WITH_UUID=yes"

EXTRA_OEMAKE_WEBSOCKETS = "WITH_WEBSOCKETS=no"
EXTRA_OEMAKE_WEBSOCKETS:USE_mosquitto_websockets = "WITH_WEBSOCKETS=yes"

EXTRA_OEMAKE = "\
  ${EXTRA_OEMAKE_UUID} \
  ${EXTRA_OEMAKE_WEBSOCKETS} \
  WITH_SRV=no \
  WITH_DOCS=no \
  prefix=${prefix} \
"
