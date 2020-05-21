# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_type.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/11/13 04:02:26 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "type"
	# launch "parser"
	# test_launch 'type -q '
	# test_launch 'type -z -q -r'
	# test_launch 'type -v -e -l'

	launch_show "Simple tests"
	test_launch 'type ; echo $?'
	test_launch 'type ls cd brew type'
	test_launch 'type ls cd brew none type'
	test_launch 'type ls cd brew type none'
	test_launch 'ls ; type ls cd brew type while'
	test_launch 'ls ; type ls cd none brew type while'
	test_launch 'ls' 'type ls cd brew type while'
	test_launch 'ls' 'type ls cd brew none type while'

	test_launch 'ls' 'alias ls=ls' 'type cd ls brew type while'
	test_launch 'ls' 'alias ls=' 'type cd ls brew  type while'
	test_launch 'ls' 'alias ls=ok ''type cd ls brew  type while'

	launch_show 'Especial'
	test_launch 'unset PATH' 'PATH=/bin' 'type ls cd'
	test_launch 'unset PATH' 'PATH=/' 'type ls cd'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 000 binary' 'type binary' 'chmod 777 binary ; rm -f binary'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 100 binary' 'type binary' 'chmod 777 binary ; rm -f binary'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 110 binary' 'type binary' 'chmod 777 binary ; rm -f binary'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 010 binary' 'type binary' 'chmod 777 binary ; rm -f binary'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 011 binary' 'type binary' 'chmod 777 binary ; rm -f binary'
	test_launch 'PATH=$PATH:./' 'touch binary ; chmod 001 binary' 'type binary' 'chmod 777 binary ; rm -f binary'

	launch_show "write"
	test_launch "type 1>&-"
	test_launch "type ls 1>&-"
	test_launch "type nothing 1>&-"
	test_launch "type -E 1>&-"
	test_launch "type -E 2>&-"
	test_launch "type 2>&-"


finish
