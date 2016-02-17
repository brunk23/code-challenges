#!/bin/sh
# Script to solve problem posed in this thread.
# I am frob23 in the thread, found this old file and am adding it to archive
# http://www.linuxquestions.org/questions/linux-general-1/replacing-situation-with-sed-4175430750/
PARAM="$1"
VALUE="$2"

sed "s/${PARAM}[ 	]*=.*/${PARAM} = ${VALUE}/"
