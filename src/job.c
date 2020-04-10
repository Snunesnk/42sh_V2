/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:35 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 15:14:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

void	free_all_processes(t_process *p)
{
	t_process	*next_p;

	while (p)
	{
		next_p = p->next;
		free_process(p);
		p = next_p;
	}
}

void	free_job(t_job *j)
{
	t_job	*j_next;
	t_job	*tmp;

	if (j == first_job)
	{
		free_all_processes(j->first_process);
		free(j);
		first_job = NULL;
	}
	else
	{
		j_next = first_job;
		while (j_next && j_next->next)
		{
			if (j_next->next->pgid == j->pgid)
			{
				tmp = j_next->next;
				j_next->next = tmp->next;
				free_all_processes(tmp->first_process);
				free(tmp);
				return ;
			}
			j_next = j_next->next;
		}
	}
}

int		launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	mypipe[0] = -1;
	mypipe[1] = -1;
	outfile = -1;
	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (treat_expansions(p))
			p->argv[0] = NULL;
		if (p->next)
		{
			if (pipe(mypipe) < 0)
			{
				perror("pipe");
				exit(1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		if (!j->first_process->next && only_assignments(p))
			treat_shell_variables(p, 1);
		else if (outfile == j->stdout && is_a_builtin(p->argv[0]) \
				&& !j->first_process->next)
		{
			treat_shell_variables(p, 0);
			return (launch_builtin(p));
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (infile != mypipe[0] && mypipe[0] != -1)
					close(mypipe[0]);
				treat_shell_variables(p, 1);
				launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
			}
			else if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			else
			{
				p->pid = pid;
				if (shell_is_interactive)
				{
					if (!j->pgid)
						j->pgid = pid;
					setpgid(pid, j->pgid);
				}
				add_name_hash_table(p->argv[0], 1);
			}
		}
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}
	if (!shell_is_interactive)
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
	return (-1);
}
