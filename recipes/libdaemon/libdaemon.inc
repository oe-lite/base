DESCRIPTION = "libdaemon is a lightweight C library that eases the writing of \
	UNIX daemons."
AUTHOR = "Lennart Poettering <lennart@poettering.net>"
HOMEPAGE = "http://0pointer.de/lennart/projects/libdaemon/"

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://0pointer.de/lennart/projects/libdaemon/libdaemon-${PV}.tar.gz"

inherit autotools pkgconfig library

EXTRA_OECONF = "--disable-lynx --disable-doxygen"
