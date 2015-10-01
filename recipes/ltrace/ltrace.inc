DESCRIPTION = "ltrace shows runtime library call information for dynamically linked executables."
HOMEPAGE = "http://ltrace.alioth.debian.org"
DEPENDS = "libelf libsupc++"
LICENSE = "GPLv2"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit make c

do_configure[prefuncs] += "do_configure_archs"
do_configure_archs() {
	case ${TARGET_ARCH} in
		arm*)  ln -sf ./linux-gnu sysdeps/linux-gnueabi ;;
		mips*)  ln -sf ./mipsel sysdeps/linux-gnu/mips ;;
	esac
	sed -i -e 's:uname -m:echo @HOST_CPU@:' \
		sysdeps/linux-gnu/Makefile
}

do_configure () {
	./configure CC=${CC} prefix=${prefix} sysconfdir=${sysconfdir}
}

export LTRACE_ARCH=""
do_compile() {
	case ${TARGET_ARCH} in
		alpha*)   LTRACE_ARCH=alpha ;;
		arm*)     LTRACE_ARCH=arm ;;
		cris*)    LTRACE_ARCH=cris ;;
		hppa*)    LTRACE_ARCH=parisc ;;
		i*86*)    LTRACE_ARCH=i386 ;;
		ia64*)    LTRACE_ARCH=ia64 ;;
		mips*)    LTRACE_ARCH=mips ;;
		m68k*)    LTRACE_ARCH=m68k ;;
		powerpc*) LTRACE_ARCH=ppc ;;
		s390*)    LTRACE_ARCH=s390 ;;
		sh*)      LTRACE_ARCH=sh ;;
		sparc64*) LTRACE_ARCH=sparc64 ;;
		sparc*)   LTRACE_ARCH=sparc ;;
		x86_64*)  LTRACE_ARCH=x86_64 ;;
	esac
	oe_runmake LIBS="-lsupc++ -Wl,-Bstatic -lelf -Wl,-Bdynamic" ${EXTRA_OEMAKE} ARCH=$LTRACE_ARCH
}

do_install() {
	case ${TARGET_ARCH} in
		alpha*)   LTRACE_ARCH=alpha ;;
		arm*)     LTRACE_ARCH=arm ;;
		cris*)    LTRACE_ARCH=cris ;;
		hppa*)    LTRACE_ARCH=parisc ;;
		i*86*)    LTRACE_ARCH=i386 ;;
		ia64*)    LTRACE_ARCH=ia64 ;;
		mips*)    LTRACE_ARCH=mips ;;
		m68k*)    LTRACE_ARCH=m68k ;;
		powerpc*) LTRACE_ARCH=ppc ;;
		s390*)    LTRACE_ARCH=s390 ;;
		sh*)      LTRACE_ARCH=sh ;;
		sparc64*) LTRACE_ARCH=sparc64 ;;
		sparc*)   LTRACE_ARCH=sparc ;;
		x86_64*)  LTRACE_ARCH=x86_64 ;;
	esac
	oe_runmake install ${EXTRA_OEMAKE} ARCH=$LTRACE_ARCH DESTDIR=${D}
}

DEPENDS_${PN} += "libc"
RDEPENDS_${PN} += "libc"
