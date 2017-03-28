SUMMARY = "poll is a command-line tool to bring \"poll(2)\" syscall functionality to the command line"

LICENSE = "GPL-3.0+"
SRC_URI = "git://github.com/mentalisttraceur/poll;${SRC_REV}"

RECIPE_TYPES = "machine native"
COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c

S = "${SRCDIR}/${PN}"

do_compile() {
    ${CC} ${CFLAGS} -std=gnu99 -o poll poll.c
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 poll ${D}${bindir}
}

DEPENDS_${PN} = "libc"
RDEPENDS_${PN} = "libc"
