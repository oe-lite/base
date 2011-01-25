DESCRIPTION = "Tools for managing memory technology devices."
HOMEPAGE = "http://www.linux-mtd.infradead.org/"
LICENSE = "GPLv2"
SECTION = "base"

BBCLASSEXTEND = "native"

DEPENDS = "libz${RE} liblzo${RE} libuuid${RE} ${SYSROOT_DEPENDS}"
SYSROOT_DEPENDS = "${HOST_ARCH}/sysroot-libm"
SYSROOT_DEPENDS_recipe-native = ""

SRC_URI = "git://git.infradead.org/mtd-utils.git;protocol=git;tag=v${PV}"

S = "${SRCDIR}/git/"

EXTRA_OEMAKE = "'LDFLAGS=${LDFLAGS}' \
    'CFLAGS=${CFLAGS} -I${S}/include -DWITHOUT_XATTR'"
EXTRA_OEMAKE_append_recipe-native += "'PREFIX=${prefix}' 'SBINDIR=${bindir}'"

do_install () {
    oe_runmake install DESTDIR=${D}
    install -d ${D}${includedir}/mtd/
    for f in ${S}/include/mtd/*.h; do
        install -m 0644 $f ${D}${includedir}/mtd/
    done
}

PACKAGES =+ "${AUTO_PACKAGES}"

AUTO_PACKAGE_MTD_UTILS = "\
    bin2nand docfdisk doc_loadbios flashcp flash_erase flash_eraseall \
    flash_info flash_lock flash_otp_dump flash_otp_info flash_unlock \
    ftl_check ftl_format jffs2dump mkbootenv mkfs.jffs2 mkfs.ubifs mkpfi \
    mtd_debug mtdinfo nand2bin nanddump nandtest nandwrite nftldump \
    nftl_format pddcustomize pfi2bin pfiflash recv_image rfddump \
    rfdformat serve_image sumtool ubiattach ubicrc32 \
    ubidetach ubiformat ubigen ubimirror ubimkvol ubinfo ubinize \
    ubirename ubirmvol ubirsvol ubiupdatevol unubi \
"

EXTRA_FILES_mtd-utils-ubicrc32 = "${sbindir}/ubicrc32.pl"

AUTO_PACKAGES_FUNC = "mtd_utils_auto_packages_func"

def mtd_utils_auto_packages_func (d):
    pn = d.getVar("PN", True)
    utils = d.getVar("AUTO_PACKAGE_MTD_UTILS", False).split()
    auto_packages = []

    def get_extra_files(pkg):
        extra_files = d.getVar("EXTRA_FILES_" + pkg, False)
        if extra_files:
            return " " + extra_files
        return ""

    for util in utils:
        pkg = "%s-%s"%(pn, util.replace("_", "-").replace(".", "-"))
        auto_packages.append(pkg)
        extra_files = get_extra_files(pkg)
        d.setVar("FILES_" + pkg,
                 "${sbindir}/%s"%(util) + extra_files)

    d.setVar("AUTO_PACKAGES", " ".join(auto_packages))
  
PACKAGES =+ "${PN}-mkfs-jffs2-doc"
FILES_${PN}-mkfs-jffs2-doc = "${mandir}/man1/mkfs.jffs2.*"

RDEPENDS_${PN}-mkfs-jffs2 = "libz${RE} liblzo${RE}"
RDEPENDS_${PN}-mkfs-ubifs = "libz${RE} liblzo${RE} libuuid${RE} \
    ${SYSROOT_RDPENDS_${PN}-mkfs-ubifs}"
SYSROOT_RDEPENDS_${PN}-mkfs-ubifs = "${HOST_ARCH}/sysroot-libm"
SYSROOT_RDEPENDS_${PN}-mkfs-ubifs_recipe-native = ""
RDEPENDS_${PN} = "${AUTO_PACKAGES}"
