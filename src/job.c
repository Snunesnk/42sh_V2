/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:35 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/03 15:32:36 by abarthel         ###   ########.fr       */
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

void	free_job(t_job *j) /* Free a given job in the job queue */
{
	t_job	*j_next;
	t_job	*tmp;

	if (j == first_job)
	{
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

void	launch_job(t_job *j, int foreground)
{
	t_process *p;
	pid_t pid;
	int mypipe[2], infile, outfile;

	outfile = -1;
	infile = j->stdin;
	p = j->first_process;
	mypipe[0] = -1;
	mypipe[1] = -1;
	while (p)
	{
//		treat_expansions(p->argc, p->argv);
//		ft_printf("\n>%s\n", p->argv[1]);
		if (treat_expansions(p->argc, p->argv)) /* If expansion fails, the process execution is skipped */
		{ /* test pipe: echo Hello | ${${dfdf}} | cat -e */
			p->argv[0] = NULL; /* Should be free instead */
		}
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

		/* 1. Check if process is a shell builtin, NOFORK */
		if (outfile == j->stdout && is_a_builtin(p->argv[0]) && !j->first_process->next)
		{
			g_retval = launch_builtin(p);
			return ;
		}
		/* 2. Fork the child processes.  */
		else
		{
			pid = fork ();
			if (pid == 0)
			{
				/* This is the child process.  */
				if (infile != mypipe[0] && mypipe[0] != -1)
					close(mypipe[0]);
				launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
			}
			else if (pid < 0)
			{
				/* The fork failed.  */
				perror ("fork");
				exit (1);
			}
			else
			{
				/* This is the parent process.  */
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

		/* Clean up after pipes.  */
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}


	if (!shell_is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
	{
		put_job_in_background(j, 0);
		format_job_info(j, "launched");
	}
}
