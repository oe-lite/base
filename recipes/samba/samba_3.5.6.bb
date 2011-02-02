require samba.inc
require samba-basic.inc
LICENSE = "GPLv3"
S = "${SRCDIR}/samba-${PV}/source3"

SRC_URI += "file://config-h.patch"

EXTRA_OECONF += "\
	SMB_BUILD_CC_NEGATIVE_ENUM_VALUES=yes \
	samba_cv_CC_NEGATIVE_ENUM_VALUES=yes \
	linux_getgrouplist_ok=no \
	samba_cv_HAVE_BROKEN_GETGROUPS=no \
	samba_cv_HAVE_FTRUNCATE_EXTEND=yes \
	samba_cv_have_setresuid=yes \
	samba_cv_have_setresgid=yes \
	samba_cv_HAVE_WRFILE_KEYTAB=yes \
	samba_cv_linux_getgrouplist_ok=yes \
	"

do_configure() {
	# Patches we must apply by hand due to layout.
	cd ..
	patch -p1 -i ${SRCDIR}/tdbheaderfix.patch
	cd source3

	oe_runconf
}

do_compile () {
	base_do_compile
}
