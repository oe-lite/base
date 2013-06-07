require dupdate.inc

RECIPE_FLAGS += "dupdate_backend dupdate_imagemode"
DEFAULT_USE_dupdate_backend = "mtd"
DEFAULT_USE_dupdate_imagemode = "dual"
EXTRA_OECONF += "--with-backend=${USE_dupdate_backend}"
EXTRA_OECONF += "--with-imagemode=${USE_dupdate_imagemode}"
