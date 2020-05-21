# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_pwd.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:59 by jmartel           #+#    #+#              #
#    Updated: 2019/11/13 04:46:13 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "pwd"
	test_launch "/usr/bin/pwd"
	test_launch "/usr/bin/pwd | cat -e"
	test_launch "/usr/bin/pwd | cat -e | wc"
	test_launch "PWD=" "OLDPWD=" "/usr/bin/pwd"
	test_launch "/usr/bin/pwd sqs"
	test_launch "/usr/bin/pwd sqs aze"
	test_launch "mkdir dir ; cd dir ; rm -r ../dir ; /usr/bin/pwd" "cd .. ; /usr/bin/pwd"
	test_launch "cd sandbox/link/link" "/usr/bin/pwd -P"
	test_launch "cd sandbox/link/link" "/usr/bin/pwd -L"
	test_launch "cd sandbox/link/link" "/usr/bin/pwd -L -P"
	test_launch "cd sandbox/link/link" "/usr/bin/pwd -L -P -L"

	launch_show "write /usr/bin/pwd"
	test_launch "/usr/bin/pwd 1>&-"
	test_launch "/usr/bin/pwd -E 1>&-"
	test_launch "/usr/bin/pwd -E 2>&-"
	test_launch "/usr/bin/pwd 2>&-"
