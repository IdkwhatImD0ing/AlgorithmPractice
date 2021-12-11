#!/bin/bash

FILES=/home/jzhan411/CSE13S/asgn6/corpora
MYREPO=/home/jzhan411/CSE13S/asgn6
EXAMPLE=/home/jzhan411/CSE13S-resources/asgn6

(cd $MYREPO && make)

for f in $(find $FILES -type f)
do
	echo "Checking difference for $(basename $f)"
	diff <($MYREPO/encode < $f | $MYREPO/decode) $f
done
(cd $MYREPO && make clean)

