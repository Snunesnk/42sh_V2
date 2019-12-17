#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "libft.h"
#include "ft_errno.h"
#include "job_control.h"
#include "builtins.h"

int	launch_builtin(t_process *p, int infile, int outfile, int errfile, int foreground)
{
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
	/* Execute the builtin. Retreive return value */
	(void)(foreground);
	return builtins_dispatcher(p->argv);
}
