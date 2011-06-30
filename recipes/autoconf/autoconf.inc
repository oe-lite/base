DESCRIPTION = "A package of M4 macros to produce scripts to \
automatically configure sourcecode."
LICENSE = "GPLv3+-with-Autoconf-Configure-Script-Exception-v3.0"
HOMEPAGE = "http://www.gnu.org/software/autoconf/"

RECIPE_TYPES = "machine native sdk"

DEPENDS = "native:m4 native:perl"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/autoconf/autoconf-${PV}.tar.bz2"

inherit autotools

# Excluded: tests man doc
SUBDIRS = "bin . lib"

do_configure[prefuncs] += "do_configure_exclude_subdirs"
do_configure_exclude_subdirs[expand] = "2"
do_configure_exclude_subdirs() {
	if [ "${RECIPE_TYPE}" != "native" ]
	then
		export ac_cv_path_PERL="${ac_cv_path_PERL=${bindir}/perl}"
		export ac_cv_path_M4="${ac_cv_path_M4=${bindir}/m4}"
		export ac_cv_prog_gnu_m4="${ac_cv_prog_gnu_m4=yes}"
	fi
	if [ -e ${S}/Makefile.am ]
	then
		sed -i -e's,^SUBDIRS = .*,SUBDIRS = ${SUBDIRS},' ${S}/Makefile.am
	fi
}

do_configure[postfuncs] += "do_configure_replace_paths"
do_configure_replace_paths() {
	# replace paths to STAGING_BINDIR_NATIVE/perl with ${bindir}/perl
	if [ -e ${S}/bin ]
	then
		sed -i -e "1s:#!.*:#! /usr/bin/env perl:" ${S}/bin/*.in
	fi
}

PARALLEL_MAKE = ""

DEPENDS_${PN} = "native:m4 native:perl native:gnu-config"
RDEPENDS_${PN} = "m4 perl gnu-config"

FILES_${PN} += "${datadir}/autoconf"

PACKAGES += "${PN}-emacs"
FILES_${PN}-emacs += "${datadir}/emacs"
