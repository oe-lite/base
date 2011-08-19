require lzma.inc

do_compile() {
        oe_runmake -C C/Util/Lzma
        oe_runmake -C CPP/7zip/Bundles/LzmaCon/
}

do_install() {
        install -d ${D}${bindir} ${D}${libdir}
        install -m 0755 CPP/7zip/Compress/LZMA_Alone/lzma ${D}${bindir}
        oe_libinstall -a -C C/LzmaUtil liblzma ${D}${libdir}
}
