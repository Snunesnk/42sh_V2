#!/bin/bash
make -j -C ../../ ;
gcc -fsanitize=address main.c ../../libft.a -I../../include ;
./a.out ;
rm a.out ;
gcc -fsanitize=address main1.c ../../libft.a -I../../include ;
./a.out ;
rm a.out ;
