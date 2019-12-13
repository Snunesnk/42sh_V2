#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int my_launch(const char *command, char *const argv[], char *const envp[])
{
	int	status;
	pid_t	pid;

	pid = fork ();
	if (pid == 0)
	{
		/* This is the child process. Execute the shell command. */
		execve(command, argv, env);
		exit (EXIT_FAILURE);
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
