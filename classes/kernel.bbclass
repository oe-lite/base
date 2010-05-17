inherit linux-kernel-base

DEPENDS += "${TARGET_ARCH}-toolchain update-modules"
#virtual/${TARGET_PREFIX}depmod-${@get_kernelmajorversion('${PV}')} virtual/${TARGET_PREFIX}gcc${KERNEL_CCSUFFIX} 
# we include gcc above, we dont need virtual/libc
INHIBIT_DEFAULT_DEPS = "1"
INHIBIT_PACKAGE_STRIP = "1"

KERNEL_IMAGETYPE ?= "zImage"

inherit kernel-arch

export OS = "${TARGET_OS}"
export CROSS_COMPILE = "${TARGET_PREFIX}"

KERNEL_CCSUFFIX ?= ""
KERNEL_LDSUFFIX ?= ""

# Set TARGET_??_KERNEL_ARCH in the machine .conf to set architecture
# specific options necessary for building the kernel and modules.
#FIXME: should be this: TARGET_CC_KERNEL_ARCH ?= "${TARGET_CC_ARCH}"
TARGET_CC_KERNEL_ARCH ?= ""
HOST_CC_KERNEL_ARCH ?= "${TARGET_CC_KERNEL_ARCH}"
TARGET_LD_KERNEL_ARCH ?= ""
HOST_LD_KERNEL_ARCH ?= "${TARGET_LD_KERNEL_ARCH}"

KERNEL_CC = "${CCACHE}${HOST_PREFIX}gcc${KERNEL_CCSUFFIX} ${HOST_CC_KERNEL_ARCH}"
KERNEL_LD = "${LD}${KERNEL_LDSUFFIX} ${HOST_LD_KERNEL_ARCH}"

# Where built kernel lies in the kernel tree
KERNEL_OUTPUT ?= "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"
KERNEL_IMAGEDEST = "boot"



#
# configuration
#
KERNEL_VERSION = "${@get_kernelversion('${S}')}"
KERNEL_MAJOR_VERSION = "${@get_kernelmajorversion('${KERNEL_VERSION}')}"

KERNEL_LOCALVERSION ?= ""

# kernels are generally machine specific
PACKAGE_ARCH = "${MACHINE_ARCH}"

# U-Boot support
UBOOT_ENTRYPOINT ?= "20008000"
UBOOT_LOADADDRESS ?= "${UBOOT_ENTRYPOINT}"

# For the kernel, we don't want the '-e MAKEFLAGS=' in EXTRA_OEMAKE.
# We don't want to override kernel Makefile variables from the environment
EXTRA_OEMAKE = ""

kernel_do_compile() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS MACHINE
	oe_runmake include/linux/version.h CC="${KERNEL_CC}" LD="${KERNEL_LD}"
	oe_runmake ${KERNEL_IMAGETYPE} CC="${KERNEL_CC}" LD="${KERNEL_LD}"
	if (grep -q -i -e '^CONFIG_MODULES=y$' .config); then
		oe_runmake modules  CC="${KERNEL_CC}" LD="${KERNEL_LD}"
	else
		oenote "no modules to compile"
	fi
}

kernel_headers() {
        install -d ${D}/kernel
        cp -fR scripts ${D}/kernel/

	if [ -e include/generated ] ; then
		# linux/autoconf.h and others, was moved to generated/autoconf.h as of 2.6.33
		mkdir -p ${D}/kernel/include/generated
		cp -fR include/generated/* ${D}/kernel/include/generated/
	fi

	if [ -e include/asm ] ; then
		# This link is generated only in kernel before 2.6.33-rc1, don't stage it for newer kernels
		ASMDIR=`readlink include/asm`

		mkdir -p ${D}/kernel/include/$ASMDIR
		cp -fR include/$ASMDIR/* ${D}/kernel/include/$ASMDIR/
	fi
	
	# Kernel 2.6.27 moved headers from includes/asm-${ARCH} to arch/${ARCH}/include/asm
	if [ -e arch/${ARCH}/include/asm/ ] ; then
		if [ -e include/asm ] ; then
			cp -fR arch/${ARCH}/include/asm/* ${D}/kernel/include/$ASMDIR/
		fi
		install -d ${D}/kernel/arch/${ARCH}/include
		cp -fR arch/${ARCH}/* ${D}/kernel/arch/${ARCH}/
	
	# Check for arch/x86 on i386
	elif [ -d arch/x86/include/asm/ ]; then
		if [ -e include/asm ] ; then
			cp -fR arch/x86/include/asm/* ${D}/kernel/include/asm-x86/
		fi
		install -d ${D}/kernel/arch/x86/include
		cp -fR arch/x86/* ${D}/kernel/arch/x86/
	fi

	rm -f ${D}/kernel/include/asm
	ln -sf $ASMDIR ${D}/kernel/include/asm

	mkdir -p ${D}/kernel/include/asm-generic
	cp -fR include/asm-generic/* ${D}/kernel/include/asm-generic/

	mkdir -p ${D}/kernel/include/linux
	cp -fR include/linux/* ${D}/kernel/include/linux/

	mkdir -p ${D}/kernel/include/net
	cp -fR include/net/* ${D}/kernel/include/net/

	mkdir -p ${D}/kernel/include/pcmcia
	cp -fR include/pcmcia/* ${D}/kernel/include/pcmcia/

	for entry in drivers/crypto drivers/media include/media include/acpi include/sound include/video include/scsi include/trace; do
		if [ -d $entry ]; then
			mkdir -p ${D}/kernel/$entry
			cp -fR $entry/* ${D}/kernel/$entry/
		fi
	done

	if [ -d drivers/sound ]; then
		# 2.4 alsa needs some headers from this directory
		mkdir -p ${D}/kernel/include/drivers/sound
		cp -fR drivers/sound/*.h ${D}/kernel/include/drivers/sound/
	fi

	install -m 0644 .config ${D}/kernel/config-${KERNEL_VERSION}
	ln -sf config-${KERNEL_VERSION} ${D}/kernel/.config
	ln -sf config-${KERNEL_VERSION} ${D}/kernel/kernel-config
	[ -e Module.symvers ] && install -m 0644 Module.symvers ${D}/kernel/Module.symvers
	echo "${KERNEL_VERSION}" >${D}/kernel/kernel-abiversion
	echo "${KERNEL_CCSUFFIX}" >${D}/kernel/kernel-ccsuffix
	echo "${KERNEL_LDSUFFIX}" >${D}/kernel/kernel-ldsuffix
	[ -e Rules.make ] && install -m 0644 Rules.make ${D}/kernel/
	[ -e Makefile ] && install -m 0644 Makefile ${D}/kernel/
	
	# Check if arch/${ARCH}/Makefile exists and install it
	if [ -e arch/${ARCH}/Makefile ]; then
		install -d ${D}/kernel/arch/${ARCH}
		install -m 0644 arch/${ARCH}/Makefile* ${D}/kernel/arch/${ARCH}
	# Otherwise check arch/x86/Makefile for i386 and x86_64 on kernels >= 2.6.24
	elif [ -e arch/x86/Makefile ]; then
		install -d ${D}/kernel/arch/x86
		install -m 0644 arch/x86/Makefile* ${D}/kernel/arch/x86
	fi
	cp -fR include/config* ${D}/kernel/include/	
	# Install kernel images and system.map to staging
	[ -e vmlinux ] && install -m 0644 vmlinux ${D}/kernel/	
	install -m 0644 ${KERNEL_OUTPUT} ${D}/kernel/${KERNEL_IMAGETYPE}
	install -m 0644 System.map ${D}/kernel/System.map-${KERNEL_VERSION}
	[ -e Module.symvers ] && install -m 0644 Module.symvers ${D}/kernel/
}

kernel_do_install() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS MACHINE
	if (grep -q -i -e '^CONFIG_MODULES=y$' .config); then
		oe_runmake DEPMOD=echo INSTALL_MOD_PATH="${D}" modules_install
	else
		oenote "no modules to install"
	fi
	
	install -d ${D}/${KERNEL_IMAGEDEST}
	install -d ${D}/boot
	install -m 0644 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION}
	install -m 0644 System.map ${D}/boot/System.map-${KERNEL_VERSION}
	install -m 0644 .config ${D}/boot/config-${KERNEL_VERSION}
	install -m 0644 vmlinux ${D}/boot/vmlinux-${KERNEL_VERSION}
	[ -e Module.symvers ] && install -m 0644 Module.symvers ${D}/boot/Module.symvers-${KERNEL_VERSION}
	install -d ${D}/etc/modutils
        install -d ${D}/etc/modprobe.d
	
        # Check if scripts/genksyms exists and if so, build it
        if [ -e scripts/genksyms/ ]; then
                oe_runmake SUBDIRS="scripts/genksyms"
        fi

        kernel_headers
}

kernel_do_configure() {
        yes '' | oe_runmake oldconfig
}

do_menuconfig() {
	export TERMWINDOWTITLE="${PN} Kernel Configuration"
	export SHELLCMDS="make menuconfig"
	${TERMCMDRUN}
	if [ $? -ne 0 ]; then
		echo "Fatal: '${TERMCMD}' not found. Check TERMCMD variable."
		exit 1
	fi
}
do_menuconfig[nostamp] = "1"
addtask menuconfig after do_patch

inherit cml1

EXPORT_FUNCTIONS do_compile do_install do_stage do_configure

PACKAGES = "kernel kernel-base kernel-image kernel-dev kernel-vmlinux kernel-headers"
FILES = ""
FILES_kernel-image = "/boot/${KERNEL_IMAGETYPE}*"
FILES_kernel-dev = "/boot/System.map* /boot/Module.symvers* /boot/config*"
FILES_kernel-vmlinux = "/boot/vmlinux*"
FILES_kernel-headers = "/kernel"
RDEPENDS_kernel = "kernel-base"
# Allow machines to override this dependency if kernel image files are 
# not wanted in images as standard
RDEPENDS_kernel-base ?= "kernel-image"
ALLOW_EMPTY_kernel = "1"
ALLOW_EMPTY_kernel-base = "1"
ALLOW_EMPTY_kernel-image = "1"

# Support checking the kernel size since some kernels need to reside in partitions
# with a fixed length or there is a limit in transferring the kernel to memory
do_sizecheck() {
	if [ ! -z "${KERNEL_IMAGE_MAXSIZE}" ]; then
        	size=`ls -l arch/${ARCH}/boot/${KERNEL_IMAGETYPE} | awk '{ print $5}'`
        	if [ $size -ge ${KERNEL_IMAGE_MAXSIZE} ]; then
                	rm arch/${ARCH}/boot/${KERNEL_IMAGETYPE}
                	die  "This kernel (size=$size > ${KERNEL_IMAGE_MAXSIZE}) is too big for your device. Please reduce the size of the kernel by making more of it modular."
        	fi
    	fi
}

addtask sizecheck before do_install after do_compile

KERNEL_IMAGE_BASE_NAME ?= "${KERNEL_IMAGETYPE}-${PV}-${PR}-${MACHINE}-${DATETIME}"
KERNEL_IMAGE_SYMLINK_NAME ?= "${KERNEL_IMAGETYPE}-${MACHINE}"
INHIBIT_KERNEL_UIMAGE_OVERRIDE ?= "0"

do_deploy() {
	install -d ${IMAGE_DEPLOY_DIR}
	install -m 0644 arch/${ARCH}/boot/${KERNEL_IMAGETYPE} ${IMAGE_DEPLOY_DIR}/${KERNEL_IMAGE_BASE_NAME}.bin
	package_stagefile_shell ${IMAGE_DEPLOY_DIR}/${KERNEL_IMAGE_BASE_NAME}.bin
	if (grep -q -i -e '^CONFIG_MODULES=y$' .config); then
		tar -cvzf ${IMAGE_DEPLOY_DIR}/modules-${KERNEL_VERSION}-${PR}-${MACHINE}.tgz -C ${D} lib
	fi
	if test "x${KERNEL_IMAGETYPE}" = "xuImage" -a "${INHIBIT_KERNEL_UIMAGE_OVERRIDE}" != "1"; then
		if test -e arch/${ARCH}/boot/compressed/vmlinux ; then
			${OBJCOPY} -O binary -R .note -R .comment -S arch/${ARCH}/boot/compressed/vmlinux linux.bin
			uboot-mkimage -A ${ARCH} -O linux -T kernel -C none -a ${UBOOT_ENTRYPOINT} -e ${UBOOT_ENTRYPOINT} -n "${DISTRO_NAME}/${PV}/${MACHINE}" -d linux.bin ${IMAGE_DEPLOY_DIR}/uImage-${PV}-${PR}-${MACHINE}-${DATETIME}.bin
			rm -f linux.bin
		else
			${OBJCOPY} -O binary -R .note -R .comment -S vmlinux linux.bin
			rm -f linux.bin.gz
			gzip -9 linux.bin
			uboot-mkimage -A ${ARCH} -O linux -T kernel -C gzip -a ${UBOOT_ENTRYPOINT} -e ${UBOOT_ENTRYPOINT} -n "${DISTRO_NAME}/${PV}/${MACHINE}" -d linux.bin.gz ${IMAGE_DEPLOY_DIR}/uImage-${PV}-${PR}-${MACHINE}-${DATETIME}.bin
			rm -f linux.bin.gz
		fi
	package_stagefile_shell ${IMAGE_DEPLOY_DIR}/uImage-${PV}-${PR}-${MACHINE}-${DATETIME}.bin
	fi

	cd ${IMAGE_DEPLOY_DIR}
	rm -f ${KERNEL_IMAGE_SYMLINK_NAME}.bin
	ln -sf ${KERNEL_IMAGE_BASE_NAME}.bin ${KERNEL_IMAGE_SYMLINK_NAME}.bin
	package_stagefile_shell ${IMAGE_DEPLOY_DIR}/${KERNEL_IMAGE_SYMLINK_NAME}.bin
}

do_deploy[dirs] = "${S}"

addtask deploy before do_package_install after do_install
