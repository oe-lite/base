DESCRIPTION = "A package of M4 macros to produce scripts to \
automatically configure sourcecode."
LICENSE = "GPLv3+-with-Autoconf-Configure-Script-Exception-v3.0"
HOMEPAGE = "http://www.gnu.org/software/autoconf/"

BBCLASSEXTEND = "native"

DEPENDS = "m4-native perl-native"

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/autoconf/autoconf-${PV}.tar.bz2"

inherit autotools

# Excluded: tests man doc
SUBDIRS = "bin . lib"

do_configure_prepend () {
        if ${@['true', 'false'][bb.data.inherits_class('native', d)]}
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

do_configure_append() {
        # replace paths to STAGING_BINDIR_NATIVE/perl with ${bindir}/perl
        if [ -e ${S}/bin ]
        then
                sed -i -e "1s:#!.*:#! /usr/bin/env perl:" ${S}/bin/*.in
        fi
}

PARALLEL_MAKE = ""

DEPENDS_${PN} = "m4-native perl-native gnu-config-native"
RDEPENDS_${PN} = "m4${RE} perl${RE} gnu-config${RE}"

FILES_${PN} += "${datadir}/autoconf"

PACKAGES += "${PN}-emacs"
FILES_${PN}-emacs += "${datadir}/emacs"
