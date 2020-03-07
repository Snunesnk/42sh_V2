#!/bin/bash
make -j -C ../../ ;
gcc -g -fsanitize=address main.c ../../libft.a -I../../include ;
#gcc -g -fsanitize=address main1.c ../../libft.a -I../../include ;
#gcc main.c ../../libft.a -I../../include ;
env -i ./a.out ;
rm a.out ;
rm -rf a.out.dSYM ;
gcc -g -fsanitize=address main1.c ../../libft.a -I../../include ;
env -i ./a.out ;
rm a.out ;
rm -rf a.out.dSYM ;
