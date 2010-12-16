DESCRIPTION = "A tool to make device nodes"
LICENSE = "GPL"
SECTION = "base"
PRIORITY = "required"
SRC_URI = "file://makedevs.c"

do_configure() {
	install -m 0644 ${WORKDIR}/makedevs.c ${S}/
}

do_compile() {
        ${CC} ${CFLAGS} -o ${S}/makedevs ${S}/makedevs.c
}

do_install() {
	install -d ${D}${sbindir}
	install -m 0755 ${S}/makedevs ${D}${sbindir}/makedevs
}

BBCLASSEXTEND = "native"
