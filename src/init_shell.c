#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"

/* Keep track of attributes of the shell. */

pid_t		shell_pgid;
struct termios	shell_tmodes;
int		shell_terminal;
int		shell_is_interactive;

/* Return value of last program and path tracking for cd builtin */
int             g_retval;
char            g_pwd[] = {0};

/* Make sure the shell is running interactively as the foreground job
before proceeding. */

int	init_shell(void)
{
	/* See if we are running interactively. */
	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive) /* Loop until we are in the foreground. */
	{
		while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())) /* check if in foreground */
		{
			kill(- shell_pgid, SIGTTIN);
		}
		/* Ignore interactive and job-control signals. */
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		/* Put ourselves in our own process group. */
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			ft_perror("Couldn't put the shell in its own process group");
			return (1);
		}
		/* Grab control of the terminal. */
		tcsetpgrp(shell_terminal, shell_pgid);
		/* Save default terminal attributes for shell. */
		tcgetattr(shell_terminal, &shell_tmodes);
	}
	return (0);
}

int	set_minimal_env(void)
{
	char	*tmp;
	int		shlvl;

	tmp = getcwd(NULL, 0);
	if (ft_setenv("PWD", tmp, 1))
		return (e_cannot_allocate_memory);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_getenv("SHLVL")))
	{
		if (ft_setenv("SHLVL", "1", 1))
			return (e_cannot_allocate_memory);
	}
	else
	{
		shlvl = ft_atoi(tmp) + 1;
		tmp = ft_itoa(shlvl);
		if (ft_setenv("SHLVL", tmp, 1))
			return (e_cannot_allocate_memory);
		ft_memdel((void**)&tmp);
	}
	if (PATH_MAX > 0)
	{
		tmp = ft_getenv("PWD");
		if (ft_strlen(tmp) <= PATH_MAX)
			ft_strcpy(g_pwd, ft_getenv("PWD"));
	}
	return (e_success);
}

void	del(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}
