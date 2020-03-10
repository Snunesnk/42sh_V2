#include "libft.h"
#include "shell.h"
#include "error.h"

/* Here will be stored the procedure to safe quit the shell */

void	free_at_exit(void);
{
	if (first_job)
	{
		free_all_jobs();
	}
}
