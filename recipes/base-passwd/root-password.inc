RECIPE_FLAGS += "passwd_root"
DEFAULT_USE_passwd_root = "$1$L9mzJfTZ$2ED5as2K2yZ98CN/BQuy1."

RECIPE_FLAGS += "passwd_rootsh"
DEFAULT_USE_passwd_rootsh = "/bin/sh"

do_install[postfuncs] += "do_install_root_password"
do_install_root_password() {
	sed -i -r \
		-e 's#^(root):\*:#\1:${USE_passwd_root}:#' \
		-e 's#^(root:.*):[^:]*#\1:${USE_passwd_rootsh}#' \
	${D}${sysconfdir}/passwd
}
