#include <stddef.h>
#include <stdlib.h>

#include "job_control.h"

t_job	*first_job = NULL;

/* MEMO: A subshell that runs non-interactively cannot and should not support job control. It
** must leave all processes it creates in the same process group as the shell itself; this allows
** the non-interactive shell and its child processes to be treated as a single job by the parent
** shell. This is easy to do—just don’t use any of the job control primitives—but you must
** remember to make the shell do it. */

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
