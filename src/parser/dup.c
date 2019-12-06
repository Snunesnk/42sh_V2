#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char	**argget(void)
{
	char **argv;

	argv = (char**)malloc(sizeof(char*) * 3);
	argv[0] = strdup("/bin/ls");
	argv[1] = strdup("-l");
	argv[2] = NULL;
	return (argv);
}

char	**argget2(void)
{
	char **argv;

	argv = (char**)malloc(sizeof(char*) * 3);
	argv[0] = strdup("/bin/cat");
	argv[1] = NULL;
	argv[2] = NULL;
	return (argv);
}

struct s_child
{
	char	*filename;
	char	**argv[];
	char	**environ;
	int	fd[2];
	int	std_fileno;
};

int	set_child_fd(struct *s_child)
{
	int stat;

	stat = 0;
	if (fd[0] != )
}


int	child_launch(void)
{
	int stat = 0;
	extern char **environ;
	int	len;
	int	fd[2];
	char	buffer[10000];

	pipe(fd);
	bzero(buffer, 10000);
	if (fork() == 0)
	{
		printf("\nFirst child\n");
		if (dup2(fd[1], STDOUT_FILENO) != -1)
		{
			if (close(fd[0]) != -1)
			{
				execve("/bin/ls", argget(), environ);
			}
		}
		exit(1);
	}
	else if (fork() == 0)
	{
		printf("\nSecond child\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execve("/bin/cat", argget2(), environ);
		exit(2);
	}
	else
	{
		wait(&stat);
		printf("\nStill in parent\n");
	}
}


int main(void)
{
	
	child_launch();
	return 0;
}
