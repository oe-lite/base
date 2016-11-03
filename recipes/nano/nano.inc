DESCRIPTION = "GNU nano (Nano's ANOther editor, or \
Not ANOther editor) is an enhanced clone of the \
Pico text editor."
HOMEPAGE = "http://www.nano-editor.org/"

inherit autotools-autoreconf gettext

COMPATIBLE_HOST_ARCHS = ".*linux"

DEPENDS = "libncurses native:texinfo"

PV_MAJOR = "${@bb.data.getVar('PV',d,1).split('.')[0]}"
PV_MINOR = "${@bb.data.getVar('PV',d,1).split('.')[1]}"
SRC_URI = "http://www.nano-editor.org/dist/v${PV_MAJOR}.${PV_MINOR}/nano-${PV}.tar.${TAREXT}"

EXTRA_OECONF = "\
    --disable-largefile \
    --disable-rpath \
    --disable-extra \
    --disable-help \
    --disable-mouse \
    --disable-speller \
    --disable-glibtest \
    --disable-utf8 \
"

PACKAGES='nano-dbg nano-doc nano-nanorc nano nano-dev nano-locale'

DEPENDS_${PN} += "libc libncurses"
RDEPENDS_${PN} += "libc libncurses ncurses"

FILES_${PN}-doc += "${datadir}/nano/man-html"
FILES_${PN}-nanorc = "${datadir}/nano/*.nanorc"
