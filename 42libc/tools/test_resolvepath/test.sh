#!/bin/bash
make -j -C ../../ ;
gcc -g -fsanitize=address main.c ../../libft.a -I../../include ;
#gcc main.c ../../libft.a -I../../include ;
./a.out ;
rm a.out ;
rm -rf a.out.dSYM ;
