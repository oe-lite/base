#!/bin/sh

OVERLAY_FILES=`cat ${OVERLAY_FILES_ETC} 2>/dev/null`
OVERLAY_DIR="${USE_overlay_files_dir}"
OVERLAY_BASE="${USE_overlay_files_base}"

for file in $OVERLAY_FILES ; do
	if test -e $OVERLAY_DIR$file ; then
		ln -sf $OVERLAY_DIR$file $OVERLAY_BASE$file
	elif test -e `basename $file`.default ; then
		ln -sf `basename $file`.default $OVERLAY_BASE$file
	fi
done
