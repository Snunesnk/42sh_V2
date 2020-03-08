#!/bin/bash

##
## This script changes some C keywords in .h and .c to make the lib 42 or ansi compliant
##
if [ "$1" == "ansi" ]
then
	if [ $(grep -a __inline__ **/*.c | wc -l) == "0" ] && [ $(grep -a __inline__ **/*.h | wc -l) == "0" ]
	then
		( shopt -s globstar dotglob
		    sed -i -- 's/inline/__inline__/g' **/*.c
		    sed -i -- 's/inline/__inline__/g' **/*.h
		)
	else
		( shopt -s globstar dotglob
		    sed -i -- 's/__inline__/inline/g' **/*.c
		    sed -i -- 's/__inline__/inline/g' **/*.h
		)
		( shopt -s globstar dotglob
		    sed -i -- 's/inline/__inline__/g' **/*.c
		    sed -i -- 's/inline/__inline__/g' **/*.h
		)
	fi
	printf "Inline ansi\n"
	if [ $(grep -a __restrict__ **/*.c | wc -l) == "0" ] && [ $(grep -a __restrict__ **/*.h | wc -l) == "0" ]
	then
		( shopt -s globstar dotglob
		    sed -i -- 's/restrict/__restrict__/g' **/*.c
		    sed -i -- 's/restrict/__restrict__/g' **/*.h
		)
	else
		( shopt -s globstar dotglob
		    sed -i -- 's/__restrict__/restrict/g' **/*.c
		    sed -i -- 's/__restrict__/restrict/g' **/*.h
		)
		( shopt -s globstar dotglob
		    sed -i -- 's/restrict/__restrict__/g' **/*.c
		    sed -i -- 's/restrict/__restrict__/g' **/*.h
		)
	fi
	printf "Restrict ansi\n"
elif [ "$1" == "42norm" ]
then
	( shopt -s globstar dotglob
	    sed -i -- 's/__inline__/inline/g' **/*.c
	    sed -i -- 's/__inline__/inline/g' **/*.h
	)
	printf "Inline 42norm\n"
	( shopt -s globstar dotglob
	    sed -i -- 's/__restrict__/restrict/g' **/*.c
	    sed -i -- 's/__restrict__/restrict/g' **/*.h
	)
	printf "Restrict 42norm\n"
fi
