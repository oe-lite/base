DESCRIPTION = "Miscellaneous files for the base system."
LICENSE = "GPL"
SECTION = "base"
PRIORITY = "required"
RDEPENDS_${PN} = "${TARGET_ARCH}/sysroot-libnss-files ${TARGET_ARCH}/sysroot-libnss-dns"

RECIPE_OPTIONS += "hostname"
DEFAULT_CONFIG_hostname = "oe-lite"

SRC_URI = " \
           file://motd \
           file://host.conf \
           file://profile \
           file://fstab \
           file://issue.net \
           file://issue \
           file://dot.bashrc \
           file://device_table-minimal.txt \
           file://nsswitch.conf \
           file://dot.profile "

# Basic filesystem directories (adheres to FHS)
dirs1777 = "/tmp \
	   ${localstatedir}/lock \
	   ${localstatedir}/tmp"
dirs2775 = "/home \
	    ${localstatedir}/local"
dirs755 = "${bindir} \
	   ${sbindir} \
	   ${libdir} \
	   ${libexecdir} \
	   ${includedir} \
	   ${sysconfdir} \
	   ${sysconfdir}/default \
	   ${sysconfdir}/skel \
	   ${prefix} \
	   ${docdir} \
	   ${datadir} \
	   ${infodir} \
	   ${mandir} \
	   ${datadir}/misc \
	   ${localstatedir} \
	   ${localstatedir}/backups \
	   ${localstatedir}/lib \
	   ${localstatedir}/lib/misc \
	   ${localstatedir}/spool \
	   ${localstatedir}/cache \
	   ${localstatedir}/log \
	   ${localstatedir}/run \
	   /sys \
	   /boot \
	   /dev \
	   /dev/pts \
	   /dev/shm \
	   /mnt \
	   /proc \
	   /root \
	   /srv \
	   /media \
	   /media/card \
	   /media/cf \
	   /media/net \
	   /media/ram \
	   /media/hdd "

FILES_${PN} = "/"

do_install () {

	# Install directories

	for d in ${dirs755}; do
		install -m 0755 -d ${D}$d
	done
	for d in ${dirs1777}; do
		install -m 1777 -d ${D}$d
	done
	for d in ${dirs2775}; do
		install -m 2755 -d ${D}$d
	done

	# Install files

        echo ${RECIPE_OPTION_base-files_hostname} > ${D}${sysconfdir}/hostname

 	install -m 0644 ${SRCDIR}/issue ${D}${sysconfdir}/issue
        install -m 0644 ${SRCDIR}/issue.net ${D}${sysconfdir}/issue.net

        echo -n "${DISTRO} " >> ${D}${sysconfdir}/issue
        echo "\n \l" >> ${D}${sysconfdir}/issue
        echo >> ${D}${sysconfdir}/issue
        
        echo -n "${DISTRO} " >> ${D}${sysconfdir}/issue.net
        echo "%h" >> ${D}${sysconfdir}/issue.net
        echo >> ${D}${sysconfdir}/issue.net
        
        install -m 0644 ${SRCDIR}/fstab ${D}${sysconfdir}/fstab
        install -m 0644 ${SRCDIR}/profile ${D}${sysconfdir}/profile
        install -m 0755 ${SRCDIR}/dot.profile ${D}${sysconfdir}/skel/.profile
        install -m 0755 ${SRCDIR}/dot.bashrc ${D}${sysconfdir}/skel/.bashrc
        install -m 0644 ${SRCDIR}/motd ${D}${sysconfdir}/motd
        install -m 0644 ${SRCDIR}/host.conf ${D}${sysconfdir}/host.conf
        install -m 0644 ${SRCDIR}/nsswitch.conf ${D}${sysconfdir}/

        ln -sf /proc/mounts ${D}${sysconfdir}/mtab
}

inherit makedevs
MAKEDEVS_FILES = "${SRCDIR}/device_table-minimal.txt"
