DESCRIPTION = "Secure rlogin/rsh/rcp/telnet replacement (OpenSSH) \
Ssh (Secure Shell) is a program for logging into a remote machine \
and for executing commands on a remote machine. \
It provides secure encrypted communications between two untrusted \
hosts over an insecure network.  X11 connections and arbitrary TCP/IP \
ports can also be forwarded over the secure channel. \
It is intended as a replacement for rlogin, rsh and rcp, and can be \
used to provide applications with a secure communication channel."
HOMEPAGE = "http://www.openssh.org/"
LICENSE = "BSD"

DEPENDS = "libcrypto${RE} libssl${RE} libz${RE} ${HOST_ARCH}/sysroot-libdl ${HOST_ARCH}/sysroot-libutil ${HOST_ARCH}/sysroot-libresolv ${HOST_ARCH}/sysroot-libcrypt"

SRC_URI = "ftp://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-${PV}.tar.gz"

SRC_URI += "file://sshd_config"
SRC_URI += "file://ssh_config"
SRC_URI += "file://init"

inherit autotools

export ASKPASS_PROGRAM = "${bindir}/ssh-askpass"
export LD = "${CC}"
CFLAGS_prepend = "-I${S} "
CFLAGS_append = " -D__FILE_OFFSET_BITS=64"
LDFLAGS_prepend = "-L${S} -L${S}/openbsd-compat "
EXTRA_OECONF = "--disable-suid-ssh --with-ssl \
	        --with-rand-helper=no \
		--without-pam \
	        --without-zlib-version-check \
		--with-privsep-path=/var/run/sshd \
		--sysconfdir=${sysconfdir}/ssh \
		--with-md5-passwords \
		--with-xauth=/usr/bin/xauth"

EXTRA_OEMAKE = "'STRIP_OPT='"

do_configure_prepend () {
	if [ ! -e acinclude.m4 -a -e aclocal.m4 ]; then
		cp aclocal.m4 acinclude.m4
	fi
}

do_compile_append () {
	install -m 0644 ${SRCDIR}/sshd_config ${S}/
	install -m 0644 ${SRCDIR}/ssh_config ${S}/
}

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${SRCDIR}/init ${D}${sysconfdir}/init.d/sshd
	rm -f ${D}${bindir}/slogin ${D}${datadir}/Ssh.bin
	rmdir ${D}/var/run/sshd ${D}/var/run ${D}/var
}

PACKAGES =+ "${PN}-keygen ${PN}-scp ${PN}-ssh ${PN}-sshd ${PN}-sftp ${PN}-misc ${PN}-sftp-server"
FILES_${PN}-scp = "${bindir}/scp"
FILES_${PN}-ssh = "${bindir}/ssh ${sysconfdir}/ssh/ssh_config"
FILES_${PN}-sshd = "${sbindir}/sshd ${sysconfdir}/init.d/sshd"
FILES_${PN}-sshd += "${sysconfdir}/ssh/moduli ${sysconfdir}/ssh/sshd_config"
FILES_${PN}-sftp = "${bindir}/sftp"
FILES_${PN}-sftp-server = "${libdir}exec/sftp-server"
FILES_${PN}-misc = "${bindir}/ssh* ${libdir}exec/ssh*"
FILES_${PN}-keygen = "${bindir}/ssh-keygen"

OPENSSH_RDEPENDS = "${HOST_ARCH}/sysroot-libdl libcrypto${RE} zlib${RE}"
RDEPENDS_${PN} += "${PN}-scp ${PN}-ssh ${PN}-sshd ${PN}-keygen"
RDEPENDS_${PN}-sshd = "${OPENSSH_RDEPENDS} ${PN}-keygen"
RDEPENDS_${PN}-ssh = "${OPENSSH_RDEPENDS}"
RDEPENDS_${PN}-scp = "${OPENSSH_RDEPENDS}"
RDEPENDS_${PN}-sftp = "${OPENSSH_RDEPENDS}"
RDEPENDS_${PN}-sftp-server = "${OPENSSH_RDEPENDS}"
RDEPENDS_${PN}-misc = "${OPENSSH_RDEPENDS}"

ALLOW_EMPTY_${PN} = "1"
