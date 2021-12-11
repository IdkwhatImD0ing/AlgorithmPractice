#!/bin/bash

FILES=/home/jzhan411/CSE13S-resources/corpora
MYREPO=/home/jzhan411/CSE13S/asgn5
EXAMPLE=/home/jzhan411/CSE13S-resources/asgn5

(cd $MYREPO && make)
(cd $EXAMPLE && clang -o error error.c && clang -o entropy entropy.c -lm)
for f in $(find $FILES -type f)
do
	echo "Checking difference for $(basename $f)"
	diff <($MYREPO/encode < $f | $MYREPO/error -e 0.01 | $MYREPO/decode) <($EXAMPLE/encode < $f | $EXAMPLE/error -e 0.01 | $EXAMPLE/decode)
done
(cd $MYREPO && make clean)
(cd $EXAMPLE && git clean -f)

