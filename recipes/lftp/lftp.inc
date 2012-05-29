DESCRIPTION = "lftp is a sophisticated command line based file \
transfer program. Supported protocols include FTP, HTTP, \
and FISH."

RECIPE_TYPES = "machine native sdk"

inherit c++ autotools-autoreconf pkgconfig largefile

DEPENDS = "libncurses libreadline"

RDEPENDS_${PN} = "libreadline"

SRC_URI = "http://ftp.yars.free.net/pub/source/lftp/lftp-${PV}.tar.bz2"
SRC_URI += "file://config.site"
SRC_HOST_SITEFILES = "${SRCDIR}/config.site"

EXTRA_OECONF = " \
--disable-rpath \
--disable-nls \
--with-gnu-ld \
--without-libresolv \
--without-gnutls \
"
