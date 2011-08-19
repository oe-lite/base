require lzma.inc

SRC_URI += "\
	file://001-large_files.patch \
	file://002-lzmp.patch \
	file://003-compile_fixes.patch \
	file://100-static_library.patch \
"

do_patch[prefuncs] += "do_patch_crlf"
do_patch_crlf() {
        # Replace MS-DOS line-endings with Unix style line-endings
        find ${S} -type f -print0 | xargs -0 sed 's/\r$//' -i
}

do_patch[postfuncs] += "do_patch_makefile_env"
do_patch_makefile_env() {
        # Hack to ensure we use our environment values
	echo CXX=$CXX
        find ${S} -type f -name makefile.gcc -print0 | xargs -0 \
		sed 's/^CXX =/CXX ?=/;s/^CXX_C =/CXX_C ?=/;s/CXX_C/CC/' -i
}

do_compile() {
        oe_runmake -C C/LzmaUtil
        oe_runmake -C CPP/7zip/Compress/LZMA_Alone
}

do_install() {
        install -d ${D}${bindir} ${D}${libdir}
        install -m 0755 CPP/7zip/Compress/LZMA_Alone/lzma ${D}${bindir}
        oe_libinstall -a -C C/LzmaUtil liblzma ${D}${libdir}
}
