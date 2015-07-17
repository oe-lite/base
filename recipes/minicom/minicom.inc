inherit autotools

SUMMARY = "Text-based modem control and terminal emulation program"

DESCRIPTION = "Minicom is a text-based modem control and terminal emulation program \
for Unix-like operating systems"

HOMEPAGE="https://alioth.debian.org/projects/minicom/"

SRC_URI = "https://alioth.debian.org/frs/download.php/file/3977/minicom-${PV}.tar.gz \
           file://allow.to.disable.lockdev.patch \
           file://0001-fix-minicom-h-v-return-value-is-not-0.patch \
          "

COMMON_DEPENDS = "libc libiconv libncurses"

DEPENDS += "${COMMON_DEPENDS}"
RDEPENDS += "${COMMON_DEPENDS}"

DEPENDS_${PN} += "${COMMON_DEPENDS}"
RDEPENDS_${PN} += "${COMMON_DEPENDS}"
