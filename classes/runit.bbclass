#
# OE-lite class for handling runit services
#

RECIPE_OPTIONS_append += "runit"

RUNIT_DEFAULT_RDEPENDS = ""
RUNIT_DEFAULT_RDEPENDS_RECIPE_OPTION_runit = "runit"
RDEPENDS_${PN}_append += "${RUNIT_DEFAULT_RDEPENDS}"

addtask install_runit after do_install before do_fixup
do_install_runit[dirs] = "${D}"

python do_install_runit () {
    import os, shutil, stat

    if not bb.data.getVar('RECIPE_OPTION_runit', d, True):
        return

    options = (bb.data.getVar('RECIPE_OPTIONS', d, True) or "").split()
    runitservicedir = bb.data.getVar('runitservicedir', d, True)
    srcdir = bb.data.getVar('SRCDIR', d, True)

    for option in options:

        if not option.endswith('_runit'):
            continue
        
        enable = bb.data.getVar('RECIPE_OPTION_'+option, d, True)
        if not enable:
            continue

	name = option[0:-len('_runit')]
        svname = bb.data.getVar('RUNIT_NAME_'+name, d, True)
        if not svname:
            svname = name.replace('_', '-')

        script = bb.data.getVar('RUNIT_SCRIPT_'+name, d, True)
        if not script:
            script = srcdir + '/' + svname + '.runit'

        dst_dir = '.%s/%s'%(runitservicedir, svname)
	dst = dst_dir + '/run'

        if not os.path.exists(script):
            bb.note('runit script not found: %s'%script)
            continue

        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        shutil.copy(script, dst)
	os.chmod(dst, stat.S_IRWXU|stat.S_IRGRP|stat.S_IXGRP|stat.S_IROTH|stat.S_IXOTH)
}
