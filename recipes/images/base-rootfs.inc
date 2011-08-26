DESCRIPTION ?= "Root filesystem"

RECIPE_TYPES = "machine"

RDEPENDS = "\
busybox \
"

export BUILD_TAG

RSTAGE_FIXUP_FUNCS += "do_version_install"
do_version_install () {
	if [ -n "$BUILD_TAG" ]; then
		echo "$BUILD_TAG" > ${SRCDIR}/build_tag
		install -m 0644 ${SRCDIR}/build_tag \
			${RSTAGE_DIR}${sysconfdir}/build_tag
	fi
}

PROVIDES_${PN} = "rootfs"
RPROVIDES_${PN} = "rootfs"
