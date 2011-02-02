require openssl.inc

SRC_URI += "file://engines-install-in-libdir-ssl.patch"

SRC_URI += "file://parallel-make.patch"
# above patch should be a step in the right direction, but not enough
PARALLEL_MAKE = ""
