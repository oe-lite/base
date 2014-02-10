LICENSE = "AGPL-3.0"
DEPENDS = "libssl libpthread libcrypto libdl libcrypt"
DEPENDS_${PN} = "libssl libpthread libcrypto libc libcrypt"
RDEPENDS_${PN} = "libssl libpthread libcrypto libc libcrypt"
inherit sysvinit

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://www.tildeslash.com/monit/dist/monit-${PV}.tar.gz\
	file://monit \
	file://fix-rebuild.patch \
	"

RECIPE_FLAGS = "monit_sysvinit_start"
DEFAULT_USE_monit_sysvinit_start = "99"

inherit autotools-autoreconf

# Workaround bug in monit config
EXTRA_OECONF = "--with-ssl-lib-dir=${TARGET_SYSROOT}${libdir} --with-ssl-incl-dir=${TARGET_SYSROOT}${includedir}"

EXTRA_OECONF =+ "--without-pam libmonit_cv_setjmp_available=yes libmonit_cv_vsnprintf_c99_conformant=yes"

do_install[postfuncs] += "do_install_fix"
do_install_fix() {
	sysvinit_install_script ${SRCDIR}/monit
        
        #Delete lines with pam
        sed -i '/allow.*@/d' ${S}/monitrc

	install -m 600 ${S}/monitrc ${D}${sysconfdir}/monitrc
	install -m 700 -d ${D}${sysconfdir}/monit.d/
}
