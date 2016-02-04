#!/bin/sh

OVERLAY_FILES=`cat ${OVERLAY_FILES_ETC} 2>/dev/null`
OVERLAY_DIR="${USE_overlay_files_dir}"
OVERLAY_BASE="${USE_overlay_files_base}"
OVERLAY_SQUASH="${USE_overlay_files_squash}"

for file in $OVERLAY_FILES ; do
    link_file="$OVERLAY_BASE$file"
    if test -n "$OVERLAY_SQUASH" -a "$OVERLAY_SQUASH" != "0" ; then
	overlay_file="$OVERLAY_DIR/"`basename "$file"`
    else
	overlay_file="$OVERLAY_DIR$file"
    fi
    if test ! -e "$overlay_file" ; then
	overlay_file="$OVERLAY_BASE$file.default"
    fi
    if test -e "$overlay_file" ; then
	if test ! -h "$link_file" -o \
	"`readlink "$link_file"`" != "$overlay_file" ; then
	    ln -sf "$overlay_file" "$link_file"
	fi
    fi
done
