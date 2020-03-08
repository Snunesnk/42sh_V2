#!/bin/bash
# Create test
ls -lRa /usr > inputs/text 

#Build GNL
make -j -C ../../
cc -g -Wall -Werror -Wextra -fsanitize=address -g main.c ../../libft.a -I../../include/ -o test
#cc -g -Wall -Werror -Wextra main.c ../../libft.a -I../../include/ -o test

# Test inputs
list=(`ls inputs`)
for elem in ${list[@]}
do
	printf "Test name: $elem\n\nNumber of lines: "
	time ./test inputs/$elem | wc -l
	printf "\n-------------------------------\n"
done

#Cleqr repository
rm inputs/text
rm -rf test.dSYM
rm test
#make fclean -C ../../
