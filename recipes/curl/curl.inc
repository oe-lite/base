SUMMARY = "curl is a command line tool for transferring data with URL syntax"
DESCRIPTION = """
curl is a command line tool for transferring data with URL syntax, supporting DICT,
 FILE, FTP, FTPS, Gopher, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, POP3, POP3S, RTMP,
 RTSP, SCP, SFTP, SMTP, SMTPS, Telnet and TFTP. curl supports SSL certificates,
 HTTP POST, HTTP PUT, FTP uploading, HTTP form based upload, proxies, cookies,
 user+password authentication (Basic, Digest, NTLM, Negotiate, kerberos...),
 file transfer resume, proxy tunneling and a busload of other useful tricks.
"""
HOMEPAGE = "http://curl.haxx.se/"

SRC_URI = "http://curl.haxx.se/download/${PN}-${PV}.tar.gz"

RECIPE_TYPES = "machine native sdk"

inherit autotools pkgconfig binconfig library auto-package-utils largefile

EXTRA_OECONF = "--disable-rtsp --disable-telnet --disable-pop3 --disable-imap --disable-gopher --disable-sspi --disable-tls-srp --disable-dict"

RECIPE_FLAGS += "curl_ipv6"
EXTRA_OECONF += "${EXTRA_OECONF_IPV6}"
EXTRA_OECONF_IPV6 = "--disable-ipv6"
EXTRA_OECONF_IPV6:USE_curl_ipv6 = "--enable-ipv6"

RECIPE_FLAGS += "curl_ssl"
DEPENDS:>USE_curl_ssl = " libssl libcrypto"
RDEPENDS_${PN}:>USE_curl_ssl = " libssl libcrypto"
EXTRA_OECONF:>USE_curl_ssl = " --with-ssl"

RECIPE_FLAGS += "curl_ldap"
DEPENDS:>USE_curl_ldap = " libldap"
RDEPENDS_${PN}:>USE_curl_ldap = " libldap"
EXTRA_OECONF += "${EXTRA_OECONF_LDAP}"
EXTRA_OECONF_LDAP = "--disable-ldap"
EXTRA_OECONF_LDAP:USE_curl_ldap = "--enable-ldap"

RECIPE_FLAGS += "curl_idn"
DEPENDS:>USE_curl_idn = " libidn"
RDEPENDS_${PN}:>USE_curl_idn = " libidn"
EXTRA_OECONF += "${EXTRA_OECONF_IDN}"
EXTRA_OECONF_IDN = "--disable-idn"
EXTRA_OECONF_IDN:USE_curl_idn = "--enable-idn"

RECIPE_FLAGS += "curl_smtp"
EXTRA_OECONF += "${EXTRA_OECONF_SMTP}"
EXTRA_OECONF_SMTP = "--disable-smtp"
EXTRA_OECONF_SMTP:USE_curl_smtp = "--enable-smtp"

RECIPE_FLAGS += "curl_ssh"
DEPENDS:>USE_curl_ssh = " libssh2"
RDEPENDS_${PN}:>USE_curl_ssh = " libssh2"
EXTRA_OECONF += "${EXTRA_OECONF_SSH}"
EXTRA_OECONF_SSH = "--disable-ssh"
EXTRA_OECONF_IDN:USE_curl_idn = "--with-libssh2"
AUTO_PACKAGE_UTILS = "curl curl-config"

DEPENDS_${PN} += "libc libgcc"
RDEPENDS_${PN} += "libc libgcc"
DEPENDS_${PN}-curl = "libc libcurl"
RDEPENDS_${PN}-curl = "libc libcurl"

RECIPE_FLAGS += "curl_ssl"
DEPENDS:>USE_curl_ssl = " libssl libcrypto"
DEPENDS_${PN}:>USE_curl_ssl = " libssl libcrypto"
RDEPENDS_${PN}:>USE_curl_ssl = " libssl libcrypto"

EXTRA_OECONF:>USE_curl_ssl += " --with-ssl"
