DESCRIPTION = "lightweight pure C websockets library"
LICENSE = "LGPL-2.1"
HOMEPAGE = "https://libwebsockets.org/"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "machine"

SRC_URI = "git://github.com/warmcat/libwebsockets;tag=v${PV}"
S = "${SRCDIR}/${PN}"

inherit cmake library auto-package-utils

DEPENDS += "libc libcrypto libm libpthread libssl libz"
DEPENDS_${PN} += "${DEPENDS}"

AUTO_PACKAGE_UTILS = "         \
    ${PN}-test-client          \
    ${PN}-test-echo            \
    ${PN}-test-fraggle         \
    ${PN}-test-fuzxy           \
    ${PN}-test-ping            \
    ${PN}-test-server          \
    ${PN}-test-server-extpoll  \
    ${PN}-test-server-pthreads \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libcrypto libdl libm libssl libz libpthread"
AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}"

FILES_${PN}-${PN}-test-server += "${datadir}/libwebsockets-test-server"

PACKAGES += "${PN}-cmake"
FILES_${PN}-cmake += "${libdir}/cmake/libwebsockets"
