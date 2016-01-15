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
LICENSE = "BSD-style"

RECIPE_TYPES = "machine"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit autotools passwd

SRC_URI = "ftp://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-${PV}.tar.gz"
SRC_URI += "file://init"
SRC_URI += "file://passwd file://group"
SRC_URI += "file://sftp-server-skip-libcrypto.patch"

DEPENDS = "libcrypto libssl libz ${DEPENDS_LIBC}"
DEPENDS_LIBC = "libdl libutil libresolv libcrypt"
DEPENDS_LIBC:HOST_LIBC_mingw = ""

export ASKPASS_PROGRAM = "${bindir}/ssh-askpass"
export LD = "${CC}"
CFLAGS =+ "-I${S} "
CFLAGS += "-D__FILE_OFFSET_BITS=64"
LDFLAGS =+ "-L${S} -L${S}/openbsd-compat"

EXTRA_OECONF = "--disable-suid-ssh --with-ssl \
	--with-rand-helper=no \
	--without-pam \
	--without-zlib-version-check \
	--with-privsep-path=/var/run/sshd \
	--sysconfdir=${sysconfdir}/ssh \
	--with-md5-passwords \
	--without-shadow \
	--with-xauth=${bindir}/xauth"

EXTRA_OEMAKE = "'STRIP_OPT='"

do_patch[postfuncs] += "do_patch_aclocal_mangle"
do_patch_aclocal_mangle () {
	if [ ! -e acinclude.m4 -a -e aclocal.m4 ]; then
		cp aclocal.m4 acinclude.m4
	fi
}

#remove unnecessary crypto dependency
do_configure[postfuncs] += "do_configure_sftp_server"
do_configure_sftp_server () {
    echo SFTP_LIBS=`grep ^LIBS= ${S}/Makefile | cut -b6- | sed 's/-lcrypto//'` >> ${S}/Makefile
}

HOST_KEY_TYPES ?= "rsa dsa ecdsa ed25519"

do_configure[postfuncs] += "do_configure_host_key_generation"
do_configure_host_key_generation() {
    sed -e 's/\(HOST_KEY_TYPES\)=.*/\1="${HOST_KEY_TYPES}"/' \
        -i ${SRCDIR}/init
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

PACKAGES =+ "${PN}-ssh-config ${PN}-sshd-config"

ALLOW_EMPTY_${PN} = "1"
FILES_${PN}-ssh = "${bindir}/slogin"
FILES_${PN}-ssh-doc = "${mandir}/*/ssh_config.* ${mandir}/*/slogin.*"
FILES_${PN}-sshd = "${sysconfdir}/init.d/sshd \
	${sysconfdir}/rcS.d/* \
	${sysconfdir}/ssh/moduli \
	${sysconfdir}/rcS.d \
	${passwddir} ${groupdir} \
	${localstatedir}/run/sshd"

FILES_${PN}-sshd-doc = "${mandir}/*/moduli.* ${mandir}/*/sshd_config.*"
FILES_${PN}-ssh-config = "${sysconfdir}/ssh/ssh_config"
FILES_${PN}-sshd-config = "${sysconfdir}/ssh/sshd_config"

RDEPENDS_${PN} += "${AUTO_PACKAGE_UTILS_PACKAGES}"
AUTO_PACKAGE_UTILS_DEPENDS = "libc libgcc libdl libutil libz libcrypto libresolv libcrypt"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libgcc libdl libutil libz libcrypto libresolv libcrypt"
RDEPENDS_${PN}-sshd = "${PN}-ssh-keygen"

RDEPENDS_${PN}-ssh-add           += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh-agent         += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh-keyscan       += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh-keygen        += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh-keysign       += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-scp               += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh               += "libcrypto libresolv libcrypt ${PN}-ssh-config"
RDEPENDS_${PN}-sshd              += "libcrypto libresolv libcrypt ${PN}-sshd-config"
RDEPENDS_${PN}-sftp              += "libcrypto libresolv libcrypt"
RDEPENDS_${PN}-ssh-pkcs11-helper += "libcrypto libresolv libcrypt"

DEPENDS_${PN}-ssh-add           += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-ssh-agent         += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-ssh-keyscan       += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-ssh-keygen        += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-scp               += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-ssh               += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-sshd              += "libc libcrypt libcrypto libdl libresolv libutil libz"
DEPENDS_${PN}-sftp              += "libc libcrypt libcrypto libdl libresolv libutil libz"

inherit sysvinit
RECIPE_FLAGS += "sshd_sysvinit_start sshd_sysvinit_stop"
DEFAULT_USE_sshd_sysvinit_start = "25"
DEFAULT_USE_sshd_sysvinit_stop = "0"

PACKAGEQA_TARGET_BINDIRS += "${target_libexecdir}"
