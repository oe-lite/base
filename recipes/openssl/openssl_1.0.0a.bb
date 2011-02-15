inherit pkgconfig

require openssl.inc

PR = "${INC_PR}.0"

SRC_URI += "file://configure-targets.patch \
            file://shared-libs.patch \
            file://debian.patch \
            file://oe-ldflags.patch \
	    file://libdeps-first.patch \
	    file://engines-install-in-libdir-ssl.patch \
	    file://openssl-fix-ssl3_get_key_exchange-double-free.patch \
	   "
