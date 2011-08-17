# -*- mode:python; -*-
DESCRIPTION = "Dropbear is a lightweight SSH and SCP Implementation"
HOMEPAGE = "http://matt.ucc.asn.au/dropbear/dropbear.html"
LICENSE = "MIT"

RECIPE_TYPES = "machine"

inherit autotools

SRC_URI = "http://matt.ucc.asn.au/dropbear/releases/dropbear-${PV}.tar.gz"
SRC_URI += "file://fix-2kb-keys.patch file://init"

RECIPE_FLAGS += "dropbear_allownopw"
SRC_URI:>USE_dropbear_allownopw = " file://allow-nopw.patch"

COMMON_DEPS = "libz libcrypt libutil libcrypt libgcc"

DEPENDS = "${COMMON_DEPS}"
RDEPENDS_${PN} = "${COMMON_DEPS}"

RPROVIDES_${PN} = "ssh sshd scp"

CFLAGS += '-D_GNU_SOURCE -DXAUTH_COMMAND=\"xauth\\ -q\"'

SBINCOMMANDS = "dropbear dropbearkey dropbearconvert"
BINCOMMANDS = "dbclient ssh scp"
EXTRA_OEMAKE = 'MULTI=1 SCPPROGRESS=1 PROGRAMS="${SBINCOMMANDS} ${BINCOMMANDS}"'
EXTRA_OECONF = "--disable-shadow "

DO_CONFIGURE_POSTFUNCS = ""
do_configure[postfuncs] += "${DO_CONFIGURE_POSTFUNCS}"

RECIPE_FLAGS += "dropbear_norevdns"

DO_CONFIGURE_POSTFUNCS:>USE_dropbear_norevdns = "do_configure_norevdns"
do_configure_norevdns() {
	sed -i -e 's|\(#define DO_HOST_LOOKUP\)$|/* \1 */|' options.h
}

# Set this if you want to use the DROPBEAR_SMALL_CODE option. This can
# save several kB in binary size however will make the symmetrical
# ciphers and hashes slower, perhaps by 50%.
RECIPE_FLAGS += "dropbear_smallcode"
DEFAULT_USE_dropbear_smallcode = "1"
DO_CONFIGURE_POSTFUNCS:>USE_dropbear_smallcode = "do_configure_smallcode"
do_configure_smallcode() {
	sed -i -e 's|/\*.*\(#define DROPBEAR_SMALL_CODE\).*$|\1|' options.h
}

do_install() {
	install -d ${D}${sysconfdir} \
		   ${D}${sysconfdir}/init.d \
	           ${D}${sysconfdir}/rcS.d \
		   ${D}${sysconfdir}/default \
		   ${D}${sysconfdir}/dropbear \
                   ${D}${bindir} \
		   ${D}${sbindir} \
		   ${D}${localstatedir}

	install -m 0755 dropbearmulti ${D}${sbindir}/
	for i in ${BINCOMMANDS}
	do
		ln -s ${sbindir}/dropbearmulti ${D}${bindir}/$i
	done
	
	for i in ${SBINCOMMANDS}
	do
		ln -s ./dropbearmulti ${D}${sbindir}/$i
	done
	cat ${SRCDIR}/init | sed -e 's,/etc,${sysconfdir},g' \
				  -e 's,/usr/sbin,${sbindir},g' \
				  -e 's,/var,${localstatedir},g' \
				  -e 's,/usr/bin,${bindir},g' \
				  -e 's,/usr,${prefix},g' \
		> ${D}${sysconfdir}/init.d/dropbear
	chmod 755 ${D}${sysconfdir}/init.d/dropbear
	ln -s ../init.d/dropbear ${D}${sysconfdir}/rcS.d/S25dropbear
}
