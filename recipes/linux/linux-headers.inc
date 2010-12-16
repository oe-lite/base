DESCRIPTION = "Sanitized Linux kernel headers"
SECTION = "devel"
LICENSE = "GPL"

DEFAULT_DEPENDS = ""

PACKAGES = "${PN}"
PROVIDES_${PN} = "linux-headers"

require conf/fetch/kernelorg.conf
SRC_URI = "${KERNELORG_MIRROR}/pub/linux/kernel/v2.6/linux-${PV}.tar.bz2"
S = "${WORKDIR}/linux-${PV}"

set_arch() {
	case ${TARGET_ARCH} in
		alpha*)   ARCH=alpha ;;
		arm*)     ARCH=arm ;;
		cris*)    ARCH=cris ;;
		hppa*)    ARCH=parisc ;;
		i*86*)    ARCH=i386 ;;
		ia64*)    ARCH=ia64 ;;
		mips*)    ARCH=mips ;;
		m68k*)    ARCH=m68k ;;
		powerpc*) ARCH=powerpc ;;
		s390*)    ARCH=s390 ;;
		sh*)      ARCH=sh ;;
		sparc64*) ARCH=sparc64 ;;
		sparc*)   ARCH=sparc ;;
		x86_64*)  ARCH=x86_64 ;;
	        avr32*)   ARCH=avr32 ;;
                bfin*)    ARCH=blackfin ;;
	esac
}

do_configure() {
	set_arch
	oe_runmake ARCH=$ARCH allnoconfig
}

do_compile () {
}

do_install() {
	set_arch
	oe_runmake ARCH=$ARCH INSTALL_HDR_PATH=${D}${exec_prefix} headers_install
}

FILES_${PN} = "${includedir}"