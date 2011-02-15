#!/bin/sh
NAME=vsftpd
DAEMON=/usr/sbin/${NAME}
DESC="Ftp Server"

[ -r /etc/default/${NAME} ] && . /etc/default/${NAME}


if [ "$VSFTPD_ENABLE" != yes ]; then
        exit 0
fi

start() {
        $DAEMON $VSFTPD_CONFIG &
	echo $! > /var/run/${NAME}.pid
}

stop() {
	kill `cat /var/run/${NAME}.pid`
}

case "$1" in
    start)
        echo -n "starting $DESC: $NAME... "
	start
	echo "done."
        ;;
    stop)
        echo -n "stopping $DESC: $NAME... "
	stop
	echo "done."
	;;
    restart)
        echo -n "restarting $DESC: $NAME... "
	stop
	start
	echo "done."
	;;
    *)
	echo "Usage: $0 {start|stop}"
	exit 1
	;;
esac
