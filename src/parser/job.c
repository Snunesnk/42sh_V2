#include <stddef.h>
#include <stdlib.h>

#include "job_control.h"

t_job			*first_job = NULL;
extern pid_t           shell_pgid;
extern struct termios  shell_tmodes;
extern int             shell_terminal;
extern int             shell_is_interactive;



/* MEMO: A subshell that runs non-interactively cannot and should not support job control. It
** must leave all processes it creates in the same process group as the shell itself; this allows
** the non-interactive shell and its child processes to be treated as a single job by the parent
** shell. This is easy to do—just don’t use any of the job control primitives—but you must
** remember to make the shell do it. */


/* Put job j in the foreground. If cont is nonzero,
restore the saved terminal modes and send the process group a
SIGCONT signal to wake it up before we block. */

/* Put the job into the foreground. */
void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(shell_terminal, j->pgid);
	/* Send the job a continue signal, if necessary. */
	if (cont)
	{
		tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
		if(kill(- j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	/* Wait for it to report. */
	 wait_for_job(j);
	/* Put the shell back in the foreground. */
	tcsetpgrp(shell_terminal, shell_pgid);
	/* Restore the shell’s terminal modes. */
	tcgetattr(shell_terminal, &j->tmodes);
	tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}





/* Find the active job with the indicated pgid. */
t_job	*find_job(pid_t pgid)
{
	t_job	*j;

	for (j = first_job; j; j = j->next)
		if (j->pgid == pgid)
			return (j);
	return (NULL);
}

/* Return true if all processes in the job have stopped or completed. */
int	job_is_stopped(t_job *j)
{
	t_process	*p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return (0);
	return (1);
}

/* Return true if all processes in the job have completed. */
int	job_is_completed(t_job *j)
{
	t_process	*p;
	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return (0);
	return (1);
}

void	launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int		mypipe[2];
	int		infile
	int		outfile;

	infile = j->stdin;
	for (p = j->first_process; p; p = p->next)
	{ /* Set up pipes, if necessary. */
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
		/* Fork the child processes. */
		pid = fork();
		if (pid == 0) /* This is the child process. */
			launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
		else if (pid < 0)
		{ /* The fork failed. */
			perror("Fork failed");
			exit(1);
		}
		else
		{ /* This is the parent process. */
			p->pid = pid;
			if (shell_is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		/* Clean up after pipes. */
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
	}
	format_job_info(j, "launched");
	if (!shell_is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
}
