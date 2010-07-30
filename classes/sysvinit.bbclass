#
# OE-lite class for handling sysvinit style init scripts and symlinks
#

addtask install_sysvinit after do_install before do_install_fixup
do_install_sysvinit[dirs] = "${D}"

sysvinit_install_script () {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 $1 ${D}${sysconfdir}/init.d/$2
}

SYSVINIT_DEFAULT_RDEPENDS = ""
SYSVINIT_DEFAULT_RDEPENDS_RECIPE_OPTION_sysvinit = "sysvinit"
RDEPENDS_${PN}_append += "${SYSVINIT_DEFAULT_RDEPENDS}"

RECIPE_OPTIONS_append += "sysvinit"

python do_install_sysvinit () {
    import os

    if not bb.data.getVar('RECIPE_OPTION_sysvinit', d, True):
        return

    options = (bb.data.getVar('RECIPE_OPTIONS', d, True) or "").split()
    sysconfdir = bb.data.getVar('sysconfdir', d, True)

    for option in options:

        if option.endswith('_sysvinit_start'):
            start_symlink = True
        elif option.endswith('_sysvinit_stop'):
            start_symlink = False
        else:
            continue
        
        prio = bb.data.getVar('RECIPE_OPTION_'+option, d, True)
        if not prio:
            continue

        if start_symlink:
            name = option[0:-len('_sysvinit_start')]
        else:
            name = option[0:-len('_sysvinit_stop')]

        script = bb.data.getVar('SYSVINIT_SCRIPT_'+name, d, True)
        if not script:
            script = name.replace('_', '-')

        src = '../init.d/%s'%(script)
        if start_symlink:
            dst_dir = '.%s/rcS.d'%(sysconfdir)
            dst_base = dst_dir + '/S'
        else:
            dst_dir = '.%s/rc0.d'%(sysconfdir)
            dst_base = dst_dir + '/K'
        dst = dst_base + prio + script
        script = '.%s/init.d/%s'%(sysconfdir, script)

        if not os.path.exists(script):
            bb.note('sysvinit script not found: %s'%script)
            continue

        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        if os.path.exists(dst):
            os.remove(dst)
        os.symlink(src, dst)
}
