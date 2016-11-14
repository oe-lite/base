COMPATIBLE_HOST_ARCHS = ".*linux"

inherit cmake sysvinit

RECIPE_FLAGS += "hiawatha_sysvinit_start hiawatha_sysvinit_stop"
DEFAULT_USE_hiawatha_sysvinit_start	= "70"
DEFAULT_USE_hiawatha_sysvinit_stop	= "0"
SYSVINIT_SCRIPT_hiawatha		= "hiawatha"

do_install[prefuncs] =+ "do_install_initscript"
do_install_initscript() {
	sysvinit_install_script ${S}/extra/debian/init.d/hiawatha hiawatha
}

SRC_URI="http://www.hiawatha-webserver.org/files/hiawatha-${PV}.tar.gz"

DEPENDS="libc libm libcrypt libpthread"
RDEPENDS_${PN} += "${DEPENDS}"

RECIPE_FLAGS += "hiawatha_cache hiawatha_debug hiawatha_ipv6 hiawatha_monitor hiawatha_rproxy hiawatha_ssl hiawatha_tomahawk hiawatha_toolkit hiawatha_xslt"
DEFAULT_USE_hiawatha_cache	= True
DEFAULT_USE_hiawatha_debug	= False
DEFAULT_USE_hiawatha_ipv6	= True
DEFAULT_USE_hiawatha_monitor	= False
DEFAULT_USE_hiawatha_rproxy	= True
DEFAULT_USE_hiawatha_ssl	= True
DEFAULT_USE_hiawatha_tomahawk	= False
DEFAULT_USE_hiawatha_toolkit	= True
DEFAULT_USE_hiawatha_xslt	= False

ENABLE_cache				="-DENABLE_CACHE=off"
ENABLE_cache:USE_hiawatha_cache		="-DENABLE_CACHE=ON"
ENABLE_debug				="-DENABLE_DEBUG=off"
ENABLE_debug:USE_hiawatha_debug		="-DENABLE_DEBUG=ON"
ENABLE_ipv6				="-DENABLE_IPV6=off"
ENABLE_ipv6:USE_hiawatha_ipv6		="-DENABLE_IPV6=ON"
ENABLE_monitor				="-DENABLE_MONITOR=off"
ENABLE_monitor:USE_hiawatha_monitor	="-DENABLE_MONITOR=ON"
ENABLE_rproxy				="-DENABLE_RPROXY=off"
ENABLE_rproxy:USE_hiawatha_rproxy	="-DENABLE_RPROXY=ON"
ENABLE_ssl				="-DENABLE_SSL=off"
ENABLE_ssl:USE_hiawatha_ssl		="-DENABLE_SSL=ON"
ENABLE_tomahawk				="-DENABLE_TOMAHAWK=off"
ENABLE_tomahawk:USE_hiawatha_tomahawk	="-DENABLE_TOMAHAWK=ON"
ENABLE_toolkit				="-DENABLE_TOOLKIT=off"
ENABLE_toolkit:USE_hiawatha_toolkit	="-DENABLE_TOOLKIT=ON"
ENABLE_xslt				="-DENABLE_XSLT=off"
ENABLE_xslt:USE_hiawatha_xslt		="-DENABLE_XSLT=ON"

EXTRA_OE_CMAKE_CONF="\
${ENABLE_cache} \
${ENABLE_debug} \
${ENABLE_ipv6} \
${ENABLE_monitor} \
${ENABLE_rproxy} \
${ENABLE_ssl} \
${ENABLE_tomahawk} \
${ENABLE_toolkit} \
${ENABLE_xslt} \
-DWEBROOT_DIR=${localstatedir}/www \
-DPID_DIR=${localstatedir}/pid \
-DCONFIG_DIR=${sysconfdir} \
-DLOG_DIR=${localstatedir}/log \
-DWORK_DIR=/tmp \
"

do_install[postfuncs] += "do_install_libpolarssl"

do_install_libpolarssl() {
	mv ${D}/usr/lib/hiawatha/* ${D}${libdir}/.
}

PACKAGES =+ "${PN}-conf"
FILES_${PN}-conf = "${sysconfdir}/hiawatha.conf"
RDEPENDS_${PN} += "${PN}-conf"

inherit auto-package-libs auto-package-utils
AUTO_PACKAGE_LIBS = "polarssl"
RDEPENDS_${PN} += "libpolarssl"

AUTO_PACKAGE_UTILS = "ssi-cgi hiawatha wigwam cgi-wrapper"
RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
