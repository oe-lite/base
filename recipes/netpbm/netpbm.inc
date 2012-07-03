DESCRIPTION = "Netpbm is a toolkit for manipulation of graphic images, including\
conversion of images between a variety of different formats.  There\
are over 220 separate tools in the package including converters for\
about 100 graphics formats."
HOMEPAGE = "http://netpbm.sourceforge.net"
LICENSE = "GPL MIT Artistic"
# NOTE: individual command line utilities are covered by different
# licenses.  The compiled and linked command line utilties are
# subject to the licenses of the libraries they use too - including
# libpng libz, IJG, and libtiff licenses

inherit c make auto-package-utils

DEPENDS = "libdl libxml2 libjpeg libpng12 tiff-dev"

require conf/fetch/sourceforge.conf
SRC_URI = " \
	${SOURCEFORGE_MIRROR}/netpbm/netpbm-${PV}.tgz \
	file://Makefile.config \
"

PARALLEL_MAKE = ""

EXTRA_OEMAKE = "'STRIPFLAG='"

do_configure() {
	cp ../Makefile.config .
}

do_install() {
	# netpbm makes its own installation package, which must then be
	# installed to form the dummy installation for ipkg
	rm -rf ${S}/netpbm-package
	oe_runmake package pkgdir=${S}/netpbm-package
	# now install the stuff from the package into ${D}
	for d in ${S}/netpbm-package/*
	do
		# following will cause an error if used
		case "$d" in
		*/README)	;;
		*/VERSION)	;;
		*/pkginfo)	;;
		*/bin)		install -d ${D}${bindir}
				cp -pPR "$d"/* ${D}${bindir}
				rm ${D}${bindir}/doc.url;;
		*/include)	install -d ${D}${includedir}
				cp -pPR "$d"/* ${D}${includedir};;
		*/link|*/lib)	install -d ${D}${libdir}
				cp -pPR "$d"/* ${D}${libdir};;
		*/man)		install -d ${D}${mandir}
				cp -pPR "$d"/* ${D}${mandir};;
		*/misc)		install -d ${D}${datadir}/netpbm
				cp -pPR "$d"/* ${D}${datadir}/netpbm;;
		*/config_template)
				install -d ${D}${bindir}
				sed "/^@/d
					s!@VERSION@!$(<'${WORKDIR}/netpbm-package/VERSION')!
					s!@DATADIR@!${datadir}/netpbm!
					s!@LIBDIR@!${libdir}!
					s!@LINKDIR@!${libdir}!
					s!@INCLUDEDIR@!${includedir}!
					s!@BINDIR@!${bindir}!
					" "$d" >${D}${bindir}/netpbm-config
				chmod 755 ${D}${bindir}/netpbm-config;;
		*)		echo "netpbm-package/$d: unknown item" >&2
				exit 1;;
		esac
	done
}

#Seperate perl scripts in package (atm not supported in OE-lite)
PACKAGES =+ "${PN}-perlscripts"
FILES_${PN}-perlscripts = "\
${bindir}/manweb \
${bindir}/pnmflip \
${bindir}/pnmquant \
${bindir}/ppmfade \
${bindir}/ppmquant \
${bindir}/ppmrainbow \
${bindir}/ppmshadow \
"

AUTO_PACKAGE_UTILS = "\
	411toppm anytopnm  gemtopnm giftopnm gouldtoppm hdifftopam hipstopgm hpcdtoppm \
	icontopbm ilbmtoppm imgtoppm infotopam jbigtopnm jpeg2ktopam jpegtopnm leaftoppm \
	lispmtopgm macptopbm mdatopbm mgrtopbm mrftopbm mtvtoppm neotoppm netpbm-config \
	palmtopnm pamaddnoise pamarith pambayer pamchannel pamcomp pamcut pamdeinterlace \
	pamdepth pamdice pamditherbw pamedge pamendian pamenlarge pamfile pamflip pamfunc \
	pamgauss pamgradient pamlookup pammasksharpen pammixinterlace pamoil pamperspective \
	pampick pampop9 pamrgbatopng pamscale pamseq pamsharpmap pamsharpness pamslice \
	pamsplit pamstack pamstereogram pamstretch pamstretch-gen pamsumm pamsummcol \
	pamthreshold pamtilt pamtodjvurle pamtofits pamtohdiff pamtohtmltbl pamtojpeg2k \
	pamtopfm pamtopnm pamtosvg pamtotga pamtotiff pamtouil pamtoxvmini pbmclean \
	pbmlife pbmmake pbmmask pbmpage pbmpscale pbmreduce pbmtext pbmtextps pbmto10x \
	pbmto4425 pbmtoascii pbmtoatk pbmtobbnbg pbmtocmuwm pbmtodjvurle pbmtoepsi \
	pbmtoepson pbmtoescp2 pbmtog3 pbmtogem pbmtogo pbmtoibm23xx pbmtoicon pbmtolj \
	pbmtoln03 pbmtolps pbmtomacp pbmtomatrixorbital pbmtomda pbmtomgr pbmtomrf pbmtonokia \
	pbmtopgm pbmtopi3 pbmtopk pbmtoplot pbmtoppa pbmtopsg3 pbmtoptx pbmtowbmp pbmtox10bm \
	pbmtoxbm pbmtoybm pbmtozinc pbmupc pc1toppm pcdovtoppm pcxtoppm pfmtopam pgmabel \
	pgmbentley pgmcrater pgmdeshadow pgmedge pgmenhance pgmhist pgmkernel pgmmake \
	pgmmedian pgmminkowski pgmmorphconv pgmnoise pgmnorm pgmoil pgmramp pgmslice \
	pgmtexture pgmtofs pgmtolispm pgmtopbm pgmtopgm pgmtoppm pi1toppm pi3topbm \
	picttoppm pjtoppm pktopbm pnmalias pnmarith pnmcat pnmcolormap pnmcomp pnmconvol \
	pnmcrop pnmcut pnmdepth pnmenlarge pnmfile pnmgamma pnmhisteq pnmhistmap \
	pnmindex pnminterp pnminvert pnmmargin pnmmontage pnmnlfilt pnmnoraw pnmnorm pnmpad \
	pnmpaste pnmpsnr pnmremap pnmrotate pnmscale pnmscalefixed pnmshear \
	pnmsmooth pnmsplit pnmstitch pnmtile pnmtoddif pnmtofiasco pnmtofits pnmtojbig \
	pnmtojpeg pnmtopalm pnmtopclxl pnmtoplainpnm pnmtopng pnmtopnm pnmtops pnmtorast \
	pnmtorle pnmtosgi pnmtosir pnmtotiff pnmtotiffcmyk pnmtoxwd ppm3d ppmbrighten \
	ppmchange ppmcie ppmcolormask ppmcolors ppmdcfont ppmddumpfont ppmdim ppmdist \
	ppmdither ppmdmkfont ppmdraw ppmflash ppmforge ppmglobe ppmhist ppmlabel \
	ppmmake ppmmix ppmnorm ppmntsc ppmpat ppmquantall ppmrelief \
	ppmrough ppmshift ppmspread ppmtoacad ppmtoarbtxt ppmtobmp ppmtoeyuv \
	ppmtogif ppmtoicr ppmtoilbm ppmtojpeg ppmtoleaf ppmtolj ppmtomap ppmtomitsu \
	ppmtompeg ppmtoneo ppmtopcx ppmtopgm ppmtopi1 ppmtopict ppmtopj ppmtopjxl \
	ppmtoppm ppmtopuzz ppmtorgb3 ppmtosixel ppmtoterm ppmtouil ppmtowinicon \
	ppmtoxpm ppmtoyuv ppmtoyuvsplit ppmtv ppmwheel psidtopgm pstopnm qrttoppm \
	rasttopnm rawtopgm rawtoppm rgb3toppm rlatopam rletopnm sbigtopgm sgitopnm \
	sirtopnm sldtoppm spctoppm spottopgm sputoppm svgtopam tgatoppm thinkjettopbm \
	tifftopnm wbmptopbm winicontoppm xbmtopbm ximtoppm xpmtoppm xvminitoppm xwdtopnm \
	ybmtopbm yuvsplittoppm yuvtoppm zeisstopnm pngtopnm asciitopgm atktopbm bioradtopgm \
	bmptopnm bmptoppm brushtopbm cameratopam cmuwmtopbm ddbugtopbm escp2topbm \
	eyuvtoppm fiascotopnm fitstopnm fstopgm g3topbm gemtopbm \
"

AUTO_PACKAGE_UTILS_RDEPENDS = "${PN}"

RDEPENDS_${PN}-pgmedge += "${PN}-pamedge"
RDEPENDS_${PN}-pgmnorm += "${PN}-pnmnorm"
RDEPENDS_${PN}-pgmoil += "${PN}-pamoil"
RDEPENDS_${PN}-pgmslice += "${PN}-pamslice"
RDEPENDS_${PN}-pnmarith += "${PN}-pamarith"
RDEPENDS_${PN}-pnmdepth += "${PN}-pamdepth"
RDEPENDS_${PN}-pnmenlarge += "${PN}-pamenlarge"
RDEPENDS_${PN}-pnmfile += "${PN}-pamfile"
RDEPENDS_${PN}-pnminterp += "${PN}-pamstretch"
RDEPENDS_${PN}-pnmnoraw += "${PN}-pnmtoplainpnm"
RDEPENDS_${PN}-pnmsplit += "${PN}-pamsplit"
RDEPENDS_${PN}-pnmtofits += "${PN}-pamtofits"
RDEPENDS_${PN}-pnmtopnm += "${PN}-pamtopnm"
RDEPENDS_${PN}-pnmtotiff += "${PN}-pamtotiff"
RDEPENDS_${PN}-ppmnorm += "${PN}-pnmnorm"
RDEPENDS_${PN}-ppmtojpeg += "${PN}-pnmtojpeg"
RDEPENDS_${PN}-ppmtouil += "${PN}-pamtouil"
RDEPENDS_${PN}-gemtopbm += "${PN}-gemtopnm"

RDEPENDS_${PN}-svgtopam += "libxml2 libdl"
RDEPENDS_${PN}-pnmtopng += "libpng12"
RDEPENDS_${PN}-pnmtojpeg += "libjpeg"
RDEPENDS_${PN}-pnmtotiffcmyk += "libjpeg"
RDEPENDS_${PN}-pngtopnm += "libpng12"
RDEPENDS_${PN}-tifftopnm += "libjpeg"
RDEPENDS_${PN}-pamrgbatopng += "libpng12"
RDEPENDS_${PN}-jpegtopnm += "libjpeg"
RDEPENDS_${PN}-pamtotiff += "libjpeg"
