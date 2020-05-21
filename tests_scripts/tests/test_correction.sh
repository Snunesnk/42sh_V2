# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_correction.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 01:13:40 by jmartel           #+#    #+#              #
#    Updated: 2019/11/26 08:24:56 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "correction"
	launch_show "minishell"
	test_launch 'doesnotexist' 'echo $?'
	test_launch '/bin/ls ; echo $?'
	test_launch 'ls ; echo $?'
	test_launch '/bin/ls -aFt' ' echo $?'
	test_launch '/bin/ls -A -t -F' 'echo $?'

	launch_show "21sh"
	test_launch 'ls > /tmp/ftsh_ls_out /' 'cat /tmp/ftsh_ls_out' '< /tmp/ftsh_ls_out cat -e >> /tmp/ftsh_ls_out' 'cat /tmp/ftsh_ls_out' 'rm /mp/ftsh_ls_out'
	test_launch 'echo 1 >out >&2 2>err' 'echo 2 >out 2>err' 'cat out' 'cat err' 'rm out err'
	test_launch 'echo nonstadard fd > du_fd' 'cat 4 non-standard fd' 'rm du_fd'
	test_launch 'cat <&4 2>&1 2>/dev/null'
	test_launch 'echo abc >redir_one_to_all' 'cat 9 abc' 'rm redir_one_to_all'
	test_launch 'cat <&- abc'
	test_launch 'ls doesnotexist . 2>&1 >/dev/null'
	test_launch 'ls doesnotexist . >/dev/null 2>&1'
	test_launch 'ls | sort -rn | cat -e'
	test_launch ' base64 < /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e s/1/Yes/g -e s/0/No/g'
	test_launch "ps a | grep 'base64' | grep -v 'grep'"
	test_launch 'ls -1 ; touch test_file ; ls -1' 'rm test_file'
	test_launch ' exit 1 | exit 2 | exit 3; echo stayin alive' 'echo $?'
	test_launch ' echo out >&-; echo out2' 'echo out >&- | echo out2'
	test_launch 'echo out >&- || echo out2' 'echo out >&- || echo out2'
	test_launch 'cat << END
hello world
and good
morning!
END
ls'
	test_launch 'cat << END' 'hello world' 'and good' 'morning!' 'END' 'ls'
	test_launch ' cat << EO\
F
hi
EOF'
	test_launch 'cat > /tmp/heredoc-append << FIN' 'abc' 'FIN' 'cat -e >> /tmp/heredoc-append << FIN' 'asd' 'adeqweqw' 'FIN' 'cat /tmp/heredoc-append'
	test_launch 'cat < heredoc> abd' 'ads' 'asdas' 'EOF'
	test_launch 'echo abc; exit; echo def' 'echo $?'

	launch_show 'builtin'
	test_launch 'exit 999999999999999999999999999999999999999999'
	test_launch 'exit abc' 'echo $?'
	test_launch 'exit 1 2 3 4' 'echo $?'
	test_launch 'cd ~ ; /usr/bin/pwd' 'cd /tmp ; /usr/bin/pwd'
	test_launch 'cd .././ ; /usr/bin/pwd' 'cd ../../ ; /usr/bin/pwd'
	test_launch 'cd /tmp ; /usr/bin/pwd' 'cd /bin ; /usr/bin/pwd' 'cd - ; /usr/bin/pwd'
	test_launch 'cd -L /tmp; /usr/bin/pwd;  cd -P ..' '/usr/bin/pwd'
	test_launch 'type type ls'

	launch_show "logical operators"
	test_launch 'ls -A && ls'
	test_launch 'ls doesno || echo tamer' 'echo $?'
	test_launch 'echo noerror || echo asd' 'echo $?'
	test_launch 'ifalse && echo foo || echo bar' 'true || echo foo && echo bar'

	launch_show "gestion de l'environnement"
	test_launch 'a=hello b=world; b=42 echo ${a}_${b} && echo ${b}'
	test_launch 'directory=/ ls_opt=-atr' 'ls ${ls_opt} ${directory}'
	test_launch	'echo ${empty}|cat -e'
	test_launch "set | grep -E '(a|b)='"
	test_launch "env | grep -E '(a|b)='"
	test_launch 'export b' 'printenv b'
	test_launch 'ONESHOT= env | grep ONESHOT' 'env | grep ONESHOT'
	test_launch 'unset a b' "env | grep -E '(a|b)='" "set | grep -E '(a|b)='"
	test_launch 'unset PATH' 'PATH=/bin:/usr/bin' 'mkdir testdir' 'echo ${?}' 'ls -1 | grep testdir' 'rm -rf testdir'
	test_launch 'true; echo ${?}; false; echo ${?}'

	launch_show "Partie modulaire"
	launch_show "Inhibiteurs"
	test_launch 'echo foo \'
	test_launch 'echo "\\'\''abcde\\'\''"'
	test_launch 'echo \'\'
	test_launch 'echo '\''foo\' 'bar'\'' | cat -e'
	test_launch 'echo "foo\' 'bar " | cat -e'
	test_launch 'echo "'\''foo\' 'bar'\' 'baz" | cat -e'
	test_launch 'ls\' 's \' '-lat'
	test_launch 'echo abc \|cat -e'
	test_launch 'echo abc \\|cat -e'

	launch_show 'test'
	test_launch_pipe tests_files/test/test_1
finish
