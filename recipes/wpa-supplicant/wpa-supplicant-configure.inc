do_configure[postfuncs] += "do_configure_flags"
CONF ?= "${B}/.config"
WPA_SUPPLICANT_FLAGS ?= ""

def do_configure_flags(d):
    f = open(d.get("CONF"))
    conf = f.read()
    f.close()

    for flag in (d.get("WPA_SUPPLICANT_FLAGS") or "").split():
        try:
            flag, val = flag.split("=", 1)
        except ValueError:
            val = "y"
        (conf, number_of_subs_made) = re.subn(r'^#* *'+flag+' *= *.+$', flag+'='+val, conf, flags=re.MULTILINE)
        if (number_of_subs_made > 1):
            bb.fatal('wpa-supplicant-configure multiple matches for '+flag+' in '+d.get("CONF"))
        elif (number_of_subs_made == 0):
            conf = '%s\n%s=%s\n'%(conf,flag,val)

    f = open(d.get("CONF"),"w")
    f.write(conf)
    f.close()
