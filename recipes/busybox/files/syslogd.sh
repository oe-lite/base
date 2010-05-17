#! /bin/sh
case "$1" in
    start)
	syslogd
	klogd
        ;;
esac
