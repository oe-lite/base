inherit sysvinit

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = " \
	https://mmonit.com/monit/dist/monit-${PV}.tar.gz \
	file://monit \
	file://fix-rebuild.patch \
	"

LICENSE = "AGPL-3.0"

# Upstream explicitly says "Do not run make in parallel" in response
# to a bug where the reporter used -j2.
# <https://bitbucket.org/tildeslash/monit/issues/238/make-failed>
PARALLEL_MAKE = ""

DEPENDS = "libssl libpthread libcrypto libdl libcrypt"
DEPENDS_${PN} = "libssl libpthread libcrypto libc libcrypt"
RDEPENDS_${PN} = "libssl libpthread libcrypto libc libcrypt"

RECIPE_FLAGS = "monit_sysvinit_start"
DEFAULT_USE_monit_sysvinit_start = "99"

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
