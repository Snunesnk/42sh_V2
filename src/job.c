/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:35 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 17:48:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "exec.h"

static void	j_status(t_job *j, int foreground)
{
	if (!g_shell_is_interactive)
		wait_for_job(j);
	else if (g_subshell)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
	{
		put_job_in_background(j, 0);
		format_job_info(j, "launched");
	}
}

static void	set_outfiles(t_job *j, int *infile, int *outfile, int mypipe)
{
	if (*infile != j->stdin)
		close(*infile);
	if (*outfile != j->stdout)
		close(*outfile);
	*infile = mypipe;
}

static int	set_mypipe(t_process *p, t_job *j, int mypipe[2])
{
	if (treat_expansions(p))
		p->argv[0] = NULL;
	if (p->next)
	{
		if (pipe(mypipe) < 0)
		{
			ft_dprintf(STDERR_FILENO, "System call pipe(2) failed.\n");
			exit(1);
		}
		return (mypipe[1]);
	}
	else
		return (j->stdout);
}

static void	execute(t_job *j, t_exec *e, int foreground)
{
	e->pid = fork();
	if (e->pid == 0)
	{
		if (e->infile != e->mypipe[0] && e->mypipe[0] != -1)
			close(e->mypipe[0]);
		treat_shell_variables(e->p, SET | EXPORT);
		e->p->infile = e->infile;
		e->p->errfile = j->stderr;
		e->p->outfile = e->outfile;
		launch_process(e->p, j->pgid, foreground);
	}
	else if (e->pid < 0 && ft_dprintf(STDERR_FILENO, "fork(2) failed\n"))
		exit(1);
	else
	{
		e->p->pid = e->pid;
		if (g_shell_is_interactive)
		{
			if (!j->pgid)
				j->pgid = e->pid;
			setpgid(e->pid, j->pgid);
		}
		if (g_hashall)
			add_name_hash_table(e->p->argv[0], 1);
	}
}

int			launch_job(t_job *j, int foreground)
{
	t_exec		e;

	e.mypipe[0] = -1;
	e.mypipe[1] = -1;
	e.infile = j->stdin;
	e.p = j->first_process;
	while (e.p)
	{
		e.outfile = set_mypipe(e.p, j, e.mypipe);
		if (!j->first_process->next && only_assignments(e.p))
			treat_shell_variables(e.p, SET);
		else if (e.outfile == j->stdout && is_a_builtin_command(e.p->argv) \
				&& !j->first_process->next)
			return (launch_builtin(e.p));
		else
			execute(j, &e, foreground);
		set_outfiles(j, &e.infile, &e.outfile, e.mypipe[0]);
		e.p = e.p->next;
	}
	j_status(j, foreground);
	return (-1);
}
