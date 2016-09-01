DESCRIPTION = "PHP is a popular general-purpose scripting language that is especially suited to web development."
LICENSE = "PHP-3.01"
HOMEPAGE = "http://php.net"

COMPATIBLE_HOST_ARCHS = ".*linux"
RECIPE_TYPES = "native machine"

inherit autotools c c++ pkgconfig

SRC_URI = "http://in1.php.net/distributions/php-${PV}.tar.xz"

PHP_LIBDIR = "${libdir}/php5"

DEPENDS += "libc libm libcrypt"
DEPENDS_${PN} += "libc libm libcrypt"
RDEPENDS_${PN} += "libc libm libcrypt"


EXTRA_OECONF = " \
  --libdir=${PHP_LIBDIR} \
  --with-libdir=${base_libdir} \
  --disable-all \
  --enable-json \
"

EXTRA_OEMAKE = "INSTALL_ROOT=${D}"

FILES_${PN}-dev += "${PHP_LIBDIR}/build"

RECIPE_FLAGS += "php_ssl"
DEFAULT_USE_php_ssl = True
EXTRA_OECONF_SSL = "--without-openssl"
EXTRA_OECONF_SSL:USE_php_ssl = "--with-openssl"
EXTRA_OECONF += "${EXTRA_OECONF_SSL}"
DEPENDS_SSL = ""
DEPENDS_SSL:USE_php_ssl = "libssl libcrypto"
DEPENDS += "${DEPENDS_SSL}"
DEPENDS_${PN} += "${DEPENDS_SSL}"
RDEPENDS_${PN} += "${DEPENDS_SSL}"

RECIPE_FLAGS += "php_sockets"
DEFAULT_USE_php_sockets = True
EXTRA_OECONF_SOCKETS = "--disable-sockets"
EXTRA_OECONF_SOCKETS:USE_php_sockets = "--enable-sockets"
EXTRA_OECONF += "${EXTRA_OECONF_SOCKETS}"

RECIPE_FLAGS += "php_session"
DEFAULT_USE_php_session = True
EXTRA_OECONF_SESSION = "--disable-session"
EXTRA_OECONF_SESSION:USE_php_session = "--enable-session"
EXTRA_OECONF += "${EXTRA_OECONF_SESSION}"

RECIPE_FLAGS += "php_system_pcre"
DEFAULT_USE_php_system_pcre = True
EXTRA_OECONF_SYSTEM_PCRE = ""
EXTRA_OECONF_SYSTEM_PCRE:USE_php_system_pcre = "--with-pcre-regex=${TARGET_SYSROOT}${target_prefix}"
EXTRA_OECONF += "${EXTRA_OECONF_SYSTEM_PCRE}"
DEPENDS_SYSTEM_PCRE = ""
DEPENDS_SYSTEM_PCRE:USE_php_system_pcre = "libpcre"
DEPENDS += "${DEPENDS_SYSTEM_PCRE}"
DEPENDS_${PN} += "${DEPENDS_SYSTEM_PCRE}"
RDEPENDS_${PN} += "${DEPENDS_SYSTEM_PCRE}"

RECIPE_FLAGS += "php_zlib"
DEFAULT_USE_php_zlib = True
EXTRA_OECONF_ZLIB = ""
EXTRA_OECONF_ZLIB:USE_php_zlib = "--with-zlib=${TARGET_SYSROOT}${target_prefix}"
EXTRA_OECONF += "${EXTRA_OECONF_ZLIB}"
DEPENDS_ZLIB = ""
DEPENDS_ZLIB:USE_php_zlib = "libz"
DEPENDS += "${DEPENDS_ZLIB}"
DEPENDS_${PN} += "${DEPENDS_ZLIB}"
RDEPENDS_${PN} += "${DEPENDS_ZLIB}"
