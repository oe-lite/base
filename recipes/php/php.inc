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
"

EXTRA_OEMAKE = "INSTALL_ROOT=${D}"

FILES_${PN}-dev += "${PHP_LIBDIR}/build"
