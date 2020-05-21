# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_splitting.sh                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/11/26 01:26:01 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Field_splitting"
	launch_show "simple"
		test_launch 'var="Okalmose speculos"' 'echo $var'
		test_launch 'var="-l -S .."' 'ls $var'
		test_launch 'var="-l -S"' '$var Okalmos'
		test_launch 'var="ls -NOOPT"' '$var .'
		test_launch 'var="Okalmos     Specul     os"' 'echo $var'
		test_launch "var='\"Okalmos   Speculos\"'" 'echo $var'
		test_launch 'var="echo tamer | cat -e"' '$var'
	launch_show "Old failed tests"
		test_launch 'v="Oka        Lmos" ; echo "$v"$a"$r"'
		test_launch 'v="Oka        Lmos" ; echo $v"$a""$r"'

finish
