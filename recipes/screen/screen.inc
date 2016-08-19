DESCRIPTION = "Screen is a full-screen window manager \
that multiplexes a physical terminal between several \
processes, typically interactive shells."

HOMEPAGE = "http://www.gnu.org/software/screen/"

inherit autotools autotools-autoreconf

COMPATIBLE_HOST_ARCHS = ".*linux"

SRC_URI = "http://ftp.gnu.org/gnu/screen/screen-${PV}.tar.gz \
		file://0001-compiler-sanity-checks.patch \
		file://0002-no-memcpy-fallback.patch \
		file://0003-cross-compilation-AC_TRY_RUN.patch \
		file://0004-cross-compilation-ignore-host-fs.patch \
		file://0005-avoid-identifying-as-SVR4.patch \
		file://0006-install-no-backup-binary.patch \
		file://0007-install-always-chmod.patch \
		file://0008-install-nonversioned-binary.patch \
		file://0010-rename-sched_h.patch"

EXTRA_OECONF = "--with-pty-mode=0620 --with-pty-group=5 --disable-pam"

DEPENDS = "ncurses libcrypt"
