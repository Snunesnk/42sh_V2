#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    stack_test.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:25:27 by abarthel          #+#    #+#              #
#    Updated: 2019/10/22 16:25:27 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

make -j -C ../../
cc main.c -fsanitize=address -g -Wextra -Wall ../../libft.a -I../../include -o test
./test
rm test
rm -rf test.dSYM
#make fclean -C ../../
