DESCRIPTION = "Dropbear is a lightweight SSH and SCP Implementation"
HOMEPAGE = "http://matt.ucc.asn.au/dropbear/dropbear.html"
SECTION = "console/network"
LICENSE = "MIT"

PR = "r6"

DEPENDS = "zlib-dev"
RDEPENDS_${PN} = "zlib ${HOST_ARCH}/sysroot-libgcc"

RPROVIDES_${PN} = "ssh sshd scp"

SRC_URI = "http://matt.ucc.asn.au/dropbear/releases/dropbear-${PV}.tar.gz \
	   file://fix-2kb-keys.patch;patch=1 \
	   file://init"
# add file://allow-nopw.patch to allow password-less logins

inherit autotools

CFLAGS_append += "-D_GNU_SOURCE -DXAUTH_COMMAND=\\"xauth\\ -q\\""

SBINCOMMANDS = "dropbear dropbearkey dropbearconvert"
BINCOMMANDS = "dbclient ssh scp"
EXTRA_OEMAKE = 'MULTI=1 SCPPROGRESS=1 PROGRAMS="${SBINCOMMANDS} ${BINCOMMANDS}"'
EXTRA_OECONF = "--disable-shadow "

RECIPE_OPTIONS = "dropbear_norevdns"

do_configure_append_RECIPE_OPTION_dropbear_norevdns() {
	sed -i -e 's|\(#define DO_HOST_LOOKUP\)$|/* \1 */|' options.h
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
	cat ${WORKDIR}/init | sed -e 's,/etc,${sysconfdir},g' \
				  -e 's,/usr/sbin,${sbindir},g' \
				  -e 's,/var,${localstatedir},g' \
				  -e 's,/usr/bin,${bindir},g' \
				  -e 's,/usr,${prefix},g' > ${D}${sysconfdir}/init.d/dropbear
	chmod 755 ${D}${sysconfdir}/init.d/dropbear
	ln -s ../init.d/dropbear ${D}${sysconfdir}/rcS.d/S25dropbear
}
