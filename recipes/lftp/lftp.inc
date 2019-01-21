DESCRIPTION = "lftp is a sophisticated command line based file \
transfer program. Supported protocols include FTP, HTTP, \
and FISH."

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux .*darwin"

inherit c++ autotools pkgconfig largefile

DEPENDS = "libncurses libreadline"

COMMON_DEPENDS = "libncurses libreadline libstdc++ libm libgcc libc libz"
DEPENDS_${PN} = "${COMMON_DEPENDS}"
RDEPENDS_${PN} = "${COMMON_DEPENDS}"

LFTP_MIRROR = "ftp://ftp.st.ryukoku.ac.jp/pub/network/ftp/lftp"

SRC_URI = "${LFTP_MIRROR}/lftp-${PV}.tar.bz2"
SRC_URI += "file://config.site"
SRC_HOST_SITEFILES = "${SRCDIR}/config.site"

MIRRORS += """
${LFTP_MIRROR} ${LFTP_MIRROR}/old
${LFTP_MIRROR} http://lftp.cybermirror.org
${LFTP_MIRROR} http://lftp.cybermirror.org/old
${LFTP_MIRROR} ftp://ftp.130th.net/pub/mirror/lftp
${LFTP_MIRROR} ftp://ftp.130th.net/pub/mirror/lftp/old
${LFTP_MIRROR} http://ftp.yars.free.net/pub/source/lftp/
${LFTP_MIRROR} http://ftp.yars.free.net/pub/source/lftp/old
"""

EXTRA_OECONF = " \
--disable-rpath \
--disable-nls \
--with-gnu-ld \
--without-libresolv \
--without-gnutls \
--disable-ipv6 \
--without-openssl \
--without-expat \
--without-libidn \
"
