DESCRIPTION = "Fast CGI backend (web server to CGI handler) library"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools c++ pkgconfig auto-package-utils auto-package-libs

SRC_URI = "http://www.fastcgi.com/dist/fcgi-${PV}.tar.gz"
S= "${SRCDIR}/fcgi-${PV}"

AUTO_PACKAGE_UTILS = "cgi-fcgi"
AUTO_PACKAGE_LIBS = "fcgi"
FILES_${PN}-libfcgi-dev = "${includedir}"
