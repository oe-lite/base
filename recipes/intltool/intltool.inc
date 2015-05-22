# -*- mode:python; -*-
RECIPE_TYPES = "machine native"

inherit autotools

SRC_URI += "https://launchpad.net/${PN}/trunk/${PV}/+download/${PN}-${PV}.tar.gz"

DEPENDS_${PN} += "util/xgettext util/msgmerge util/msgfmt"
RDEPENDS_${PN} += "util/xgettext util/msgmerge util/msgfmt"
