DESCRIPTON = "Init script for initramfs"

SRC_URI += "file://init"

RDEPENDS_${PN} += "mtd-utils-core"

do_install() {
        install -m 0755 ${SRCDIR}/init ${D}/init
}

FILES_${PN} = "/init"
