#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "job_control.h"

int	launch_process(process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
	pid_t	pid;
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
		if (foreground)
		{
			tcsetpgrp(shell_terminal, pgid);
		}
		/* Set the handling for job control signals back to the default. */
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	/* Set the standard input/output channels of the new process. */
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
	/* Exec the new process. Make sure we exit */
	execve(p->argv[0], p->argv);
	perror("Failed to launch process using execve");
	exit(1);
}

int my_launch(const char *command, char *const argv[], char *const envp[])
{
	int	status;
	pid_t	pid;

	pid = fork ();
	if (pid == 0)
	{
		/* This is the child process. Execute the shell command. */
		status = launch_process();
		exit(status);
	}
	else if (pid < 0)
	{
		/* The fork failed. Report failure. */
		status = -1;
	}
	else
	{
		/* This is the parent process. Wait for the child to complete. */
		if (waitpid (pid, &status, 0) != pid)
			status = -1;
	}
	return (status);
}
