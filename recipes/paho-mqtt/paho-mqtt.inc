SUMMARY = "Eclipse Paho MQTT C client"
HOMEPAGE = "https://github.com/eclipse/paho.mqtt.c"
RECIPE_TYPES = "machine native"
LICENSE = "EPL-1.0"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit cmake c auto-package-libs

SRC_URI = "https://github.com/eclipse/paho.mqtt.c/archive/v${PV}.tar.gz"

S="${SRCDIR}/paho.mqtt.c-${PV}"

DEPENDS += "libdl libpthread"
DEPENDS_${PN} += "libpaho-mqtt3a libpaho-mqtt3c"
RDEPENDS_${PN} += "libpaho-mqtt3a libpaho-mqtt3c"

AUTO_PACKAGE_LIBS = "paho-mqtt3a paho-mqtt3c"
AUTO_PACKAGE_LIBS_DEPENDS = "libdl libpthread"
AUTO_PACKAGE_LIBS_RDEPENDS = "libc libdl libpthread"
