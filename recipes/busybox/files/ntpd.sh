#!/bin/sh
. /etc/default/rcS

case "$1" in
    start)
	ntpd $NTPSERVERS
        ;;
esac
