/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 11:58:40 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"
#include "builtins.h"

void	free_process(t_process *p)
{
	free_redirections(p->redir);
	free(p->argv);
	free(p);
}

int	launch_process(t_process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
	char		**envp;
	pid_t		pid;
	int			ret;

	if (!p->argv[0])
		exit(1);
	envp = get_env_tab();
	if (shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (!g_subshell && foreground)
			tcsetpgrp(shell_terminal, pgid);
		restore_procmask();
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	if ((ret = do_redirection(p->redir)))
	{
		free_process(p);
		exit(g_errordesc[ret].code);
	}
	ret = execute_process(p->argv, envp, NULL, NULL);
	free_process(p);
	exit(ret);
}
