DESCRIPTION = "Network performance benchmark including tests for TCP, UDP, sockets, ATM and more."
HOMEPAGE = "http://www.netperf.org/"
LICENSE = "netperf"

COMPATIBLE_HOST_ARCHS = ".*linux"

NETPERF_MIRROR = "ftp://ftp.netperf.org/netperf"
SRC_URI = "${NETPERF_MIRROR}/netperf-${PV}.tar.bz2"

SRC_URI += "file://init"

MIRRORS =. """
${NETPERF_MIRROR} ${NETPERF_MIRROR}/archive
"""

inherit autotools siteinfo

DEPENDS += "libm libdl"

CFLAGS += "-DDO_UNIX -D_GNU_SOURCE"

RECIPE_FLAGS += "netperf_ipv6"
CFLAGS:>USE_netperf_ipv6 = " -DDO_IPV6"

RECIPE_FLAGS += "netperf_histogram"
EXTRA_OECONF:>USE_netperf_histogram = " --enable-histogram"

RECIPE_FLAGS += "netperf_intervals"
EXTRA_OECONF:>USE_netperf_intervals = " --enable-intervals"

RECIPE_FLAGS += "netperf_spin"
EXTRA_OECONF:>USE_netperf_spin = " --enable-spin"

RECIPE_FLAGS += "netperf_burst"
EXTRA_OECONF:>USE_netperf_burst = " --enable-burst"

do_install() {
        install -d ${D}${sbindir} ${D}${bindir} ${D}${sysconfdir}/init.d
        install -m 4755 src/netperf ${D}${bindir}
        install -m 4755 src/netserver ${D}${sbindir}
        install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/netperf

        # man
        install -d ${D}${mandir}/man1/
        install -m 0644 doc/netserver.man ${D}${mandir}/man1/netserver.1
        install -m 0644 doc/netperf.man ${D}${mandir}/man1/netperf.1

        # move scripts to examples directory
        install -d ${D}${docdir}/netperf/examples
        install -m 0644 doc/examples/*_script ${D}${docdir}/netperf/examples/

        # docs ..
        install -m 0644 COPYING ${D}${docdir}/netperf
        install -m 0644 Release_Notes ${D}${docdir}/netperf
        install -m 0644 README ${D}${docdir}/netperf
        install -m 0644 doc/netperf_old.ps ${D}${docdir}/netperf

	# init scripts
	install -d 755 ${D}${sysconfdir}/init.d
	install -m 755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/netperf
	#ln -s ../init.d/netperf ${D}${sysconfdir}/rcS.d/S99netperf
}
