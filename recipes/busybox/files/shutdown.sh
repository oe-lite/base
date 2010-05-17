#!/bin/sh

# FIXME: we should signal Application Watchdog Monitor that we are
# rebooting, thus causing it to go to it's reboot state with reboot
# timeout armed

kill -TERM -1
sync
ps |grep -v "AND$\|]$"

kill -KILL -1
umount -a -r -n
