SUMMARY = "DNS management framework"
DESCRIPTION = "Resolvconf is a framework for keeping track of the system's \
information about currently available nameservers. It sets \
itself up as the intermediary between programs that supply \
nameserver information and programs that need nameserver \
information. \
\
This package is an alternative to Debian's resolvconf implementation \
"
LICENSE = "BSD-2-Clause"
HOMEPAGE = "https://roy.marples.name/projects/openresolv"

SRC_URI = "https://roy.marples.name/downloads/openresolv/openresolv-${PV}.tar.xz"

# Not autotools, but with autotools-mostly-compatible configure script
inherit autotools

PROVIDES_${PN} += "util/resolvconf"
PACKAGES =+ "${PN}-config"
FILES_${PN}-config = "${sysconfdir}/resolvconf.conf"
RDEPENDS_${PN} += "${PN}-config"

do_install_sanitize_config() {
  conf="${D}/${sysconfdir}/resolvconf.conf"

  tweak() {
    # The packaged one doesn't end in a newline, tsk tsk
    echo ""

    echo "### OE-lite default tweaks follow" >> $conf
    echo "# Disable all hooks except libc" >> $conf
    for hook in ${D}/${libexecdir}/* ; do
      f=$(basename $hook)
      if [ "$f" = libc ] ; then continue ; fi
      echo "$f=no" >> $conf
    done

    echo "# Avoid doing an expensive and likely failing init system"
    echo "# probing for how to restart \$libc_service aka nscd, which"
    echo "# probably isn't running on target anyway."
    echo "libc_restart=true"
  }
  tweak >> $conf
}
do_install[postfuncs] += "do_install_sanitize_config"
