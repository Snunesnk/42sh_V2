#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    runtest.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 09:49:39 by abarthel          #+#    #+#              #
#    Updated: 2019/10/31 09:49:39 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TEST STACK
cd test_stack/
./stack_test.sh
cd ..

# TEST QUEUE
cd test_queue/
./queue_test.sh
cd ..

# TEST GETNEXTLINE
cd test_gnl/
./gnl_test.sh
cd ..

# TEST NMEMDEL
cd test_nmemdel/
./nmemdel_test.sh
cd ..

# TEST BTREE
cd test_btree/
./btree_test.sh
cd ..

# CLEAR REPO
make fclean -C ../
