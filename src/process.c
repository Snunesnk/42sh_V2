/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 17:44:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"
#include "builtins.h"

void	free_process(t_process *p) /* temporary for tests purposes ? */
{
//	ft_printf("\nFREE PROCESS\n"); /* Free a process */
	free_redirections(p->redir);
	free(p->argv);
	free(p);
}

int	launch_process(t_process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
//	extern char	**environ;
	char		**envp;
	pid_t		pid;
	int			ret;

	if (!p->argv[0]) /* Carefull and free what is needed ? */
		exit(1);
	envp = get_env_tab();
	if (shell_is_interactive)
	{ /* Put the process into the process group and give the process group
	  the terminal, if appropriate. This has to be done both by the shell
	  and in the individual child processes because of potential race conditions. */
		pid = getpid();
		if (pgid == 0)
		{
			pgid = pid;
		}
		setpgid(pid, pgid);
		if (!g_subshell && foreground)
			tcsetpgrp(shell_terminal, pgid);
		/* Set the handling for job control signals back to the default. */
		restore_procmask();
	}
	/* Set the standard input/output channels of the new process. */

	/* Pipeline common redirection, to minimise the dup of file descriptor */
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

	/* Sepcial redirections */
	if ((ret = do_redirection(p->redir)))
	{
		free_process(p);
		exit(g_errordesc[ret].code); /* redirection failure, error msg have to be implemented */
	}	/* Free or not to free ? Lazy so I leave it to exit handlers */

	/* Exec the new process. Make sure we exit */
	/* Check access, etc... and send value to exit if error launching of if builtin */
	ret = execute_process(p->argv, envp, NULL, NULL);
	free_process(p);
	exit(ret);
}
