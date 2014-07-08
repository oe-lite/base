DESCRIPTION = "Time Zone Database"
HOMEPAGE = "https://www.iana.org/time-zones"

PV_TZCODE ?= "${PV}"
PV_TZDATA ?= "${PV}"

SRC_URI = "\
ftp://ftp.iana.org/tz/releases/tzcode${PV_TZCODE}.tar.gz;subdir=${PN}-${PV} \
ftp://ftp.iana.org/tz/releases/tzdata${PV_TZDATA}.tar.gz;subdir=${PN}-${PV}"

RECIPE_TYPES = "native machine"

# Prefer these utils instead of the ones from toolchain recipe
DEFAULT_PREFERENCE = "10"

inherit c make

EXTRA_OEMAKE = '\
	cc="${CC}" \
	CFLAGS="${CFLAGS}" \
	LDFLAGS="${LDFLAGS}" \
	BINDIR="${bindir}" \
	ETCDIR="${bindir}" \
	MANDIR="${mandir}" \
	LIBDIR="${libdir}" \
	TZDIR="${datadir}/\\$(TZDIR_BASENAME)" \
	DESTDIR="${D}" \
'

# Use native:tz-zic for all builds
EXTRA_OEMAKE_native = 'zic="zic"'
EXTRA_OEMAKE_native:native = ""
EXTRA_OEMAKE += "${EXTRA_OEMAKE_native}"
DEPENDS_native = "native:util/zic"
DEPENDS_native:native = ""
DEPENDS += "${DEPENDS_native}"

EXTRA_OEMAKE_COMPILE = "ALL"
EXTRA_OEMAKE_INSTALL = "INSTALL"

FILES_${PN} = "${datadir}/zoneinfo*"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "tzselect zdump zic date"

DEPENDS_${PN}-zdump = "libc libtz"
RDEPENDS_${PN}-zdump = "libc libtz"
DEPENDS_${PN}-zic = "libc libtz"
RDEPENDS_${PN}-zic = "libc libtz"
DEPENDS_${PN}-date = "libc libtz"
RDEPENDS_${PN}-date = "libc libtz"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "tz"
PROVIDES_${PN}-libtz[qa] = "allow-missing-soname:libtz"

PACKAGES += "${PN}-utils"
DEPENDS_${PN}-utils = "${AUTO_PACKAGE_UTILS_PROVIDES}"
