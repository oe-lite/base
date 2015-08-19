DESCRIPTION = "Vi IMproved"
HOMEPAGE = "http://www.vim.org/"
LICENSE = "Vim"

inherit autotools

SRC_URI = "ftp://ftp.vim.org/pub/vim/unix/${PN}-${PV}.tar.bz2"
SRC_URI += "file://vimrc"

VIM_S = "vim${@bb.data.getVar('PV',d,1).replace('.','')}"

S = "${SRCDIR}/${VIM_S}/src"

RECIPE_TYPES = "machine"

COMPATIBLE_HOST_ARCHS = ".*linux"

DEPENDS += "libm libc libreadline libncurses libiconv zlib"
RDEPENDS += "libreadline libncurses libiconv zlib"

do_configure[prefuncs] += "do_create_configure"
do_configure[postfuncs] += "do_touch_configure"

do_create_configure() {
	rm -rf auto
	touch auto/config.mk
	aclocal
	autoconf
}

do_touch_configure() {
	touch auto/configure
	touch auto/config.mk auto/config.h
}

# VIM_FEATURES can be set to tiny, small, normal big or huge
VIM_FEATURES ?= "big"

VIM_X ?= "--without-x"
VIM_GUI ?= "no"

EXTRA_OECONF = " \
	--enable-gui=${VIM_GUI} \
	--with-features=${VIM_FEATURES} \
	${VIM_X} \
	--disable-gpm \
	--disable-gtktest \
	--disable-xim \
	--disable-netbeans \
	--with-tlib=ncurses \
	ac_cv_small_wchar_t=no \
	vim_cv_getcwd_broken=no \
	vim_cv_memmove_handles_overlap=yes \
	vim_cv_stat_ignores_slash=no \
	vim_cv_terminfo=yes \
	vim_cv_tgent=non-zero \
	vim_cv_toupper_broken=no \
	vim_cv_tty_group=world \
"

do_install() {
	oe_runmake 'DESTDIR=${D}' installvimbin installrtbase installmacros
	install -m 644 ${SRCDIR}/vimrc ${D}/usr/share/vim
}

