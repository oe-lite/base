# -*- mode:python; -*-
DESCRIPTION = "Secure rlogin/rsh/rcp/telnet replacement (OpenSSH) Ssh \
	(Secure Shell) is a program for logging into a remote machine and for \
	executing commands on a remote machine.  It provides secure encrypted \
	communications between two untrusted hosts over an insecure network. \
	X11 connections and arbitrary TCP/IP ports can also be forwarded over \
	the secure channel.  It is intended as a replacement for rlogin, rsh \
	and rcp, and can be used to provide applications with a secure \
	communication channel."
HOMEPAGE = "http://www.openssh.org/"
LICENSE = "BSD"

RECIPE_TYPES = "machine"

inherit autotools passwd

SRC_URI = "ftp://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-${PV}.tar.gz"
SRC_URI += "file://sshd_config file://ssh_config file://init"
SRC_URI += "file://passwd file://group"

DEPENDS = "libcrypto libssl libz libdl libutil libresolv libcrypt"

export ASKPASS_PROGRAM = "${bindir}/ssh-askpass"
export LD = "${CC}"
CFLAGS =+ "-I${S} "
CFLAGS += "-D__FILE_OFFSET_BITS=64"
LDFLAGS =+ "-L${S} -L${S}/openbsd-compat "

EXTRA_OECONF = "--disable-suid-ssh --with-ssl \
	--with-rand-helper=no \
	--without-pam \
	--without-zlib-version-check \
	--with-privsep-path=/var/run/sshd \
	--sysconfdir=${sysconfdir}/ssh \
	--with-md5-passwords \
	--with-xauth=${bindir}/xauth"

EXTRA_OEMAKE = "'STRIP_OPT='"

do_patch[postfuncs] += "do_patch_aclocal_mangle"
do_patch_aclocal_mangle () {
	if [ ! -e acinclude.m4 -a -e aclocal.m4 ]; then
		cp aclocal.m4 acinclude.m4
	fi
}

do_compile[postfuncs] += "do_compile_install_config_files"
do_compile_install_config_files () {
	install -m 0644 ${SRCDIR}/sshd_config ${S}/
	install -m 0644 ${SRCDIR}/ssh_config ${S}/
}

do_install[postfuncs] += "do_install_extra_files"
do_install_extra_files() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/sshd
	rm -f ${D}${bindir}/slogin ${D}${datadir}/Ssh.bin
	rmdir ${D}/var/run/sshd ${D}/var/run ${D}/var
}

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "ssh-add ssh-agent ssh-keyscan ssh-keygen ssh-keysign \
	scp ssh sshd sftp sftp-server ssh-pkcs11-helper"

ALLOW_EMPTY_${PN} = "1"
FILES_${PN}-ssh = "${sysconfdir}/ssh/ssh_config ${bindir}/slogin"
FILES_${PN}-ssh-doc = "${mandir}/*/ssh_config.* ${mandir}/*/slogin.*"
FILES_${PN}-sshd = "${sysconfdir}/init.d/sshd \
	${sysconfdir}/ssh/moduli ${sysconfdir}/ssh/sshd_config \
	${localstatedir}/run/sshd"
FILES_${PN}-sshd-doc = "${mandir}/*/moduli.* ${mandir}/*/sshd_config.*"

RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libgcc libdl libutil libcrypto libz"
RDEPENDS_${PN}-sshd = "${PN}-keygen"

inherit sysvinit
RECIPE_FLAGS = "sshd_sysvinit_start sshd_sysvinit_stop"
DEFAULT_USE_sshd_sysvinit_start = "25"
DEFAULT_USE_sshd_sysvinit_stop = "0"
