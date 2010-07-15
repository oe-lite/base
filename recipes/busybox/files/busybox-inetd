#!/bin/sh
case "$1" in
    start)
	inetd
        ;;
    reload)
	kill -HUP `cat /var/run/inetd.pid`
	;;
esac
