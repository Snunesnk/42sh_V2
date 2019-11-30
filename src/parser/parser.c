#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "ft_errno.h"
#include "ft_queue.h"
#include "error.h"
#include "tokens.h"
#include "grammar.h"
#include "syntaxic_tree.h"

#include "job.h"

void	display_tokens(t_token *token)
{
	ft_printf("symbol: %s\n", token->symbol);/* deebug */
	ft_printf("type: %d\n\n", token->type);/* deebug */
}

int	execute_jobs(t_job *s_job)
{
	t_process	*ptmp;
	extern char **environ; /* not the correct environ, should be the modified one */
	while (1) /* execute all jobs */
	{
		ptmp = s_job->first_process;
		while (2) /* execute all processes in a job */
		{
			job(ptmp->argv, environ); /* should be modified just for execution, no more path_concat at this stage */
			if (!(ptmp->next))
				break;
			ptmp = ptmp->next;
		}
		if (!(s_job->next))
			break;
		s_job = s_job->next;
	}
	return (0);
}

int	parser(struct s_queue *queue)
{
	t_token	*token;
/*	char	**argv;
*/
	queue_apply_to_each(queue, display_tokens); /* Verify tokens */

	/* Experimental This part should not be in parser, just for test during the building */
/*	extern char **environ;
*/
	t_process	*process;
	t_job		*job;

	job = (t_job*)ft_memalloc(sizeof(t_job));
	process = (t_process*)ft_memalloc(sizeof(t_process));
	size_t i = 0;
	char **ar;
	while ((token = queue_dequeue(queue, NULL)) && token->type == WORD) /* try to build a single process in a single job,
										process is a simple_command */
	{
		if (process->argv == NULL)
		{
			process->argv = (char**)ft_tabmalloc(2);
			process->argv[0] = token->symbol; /* here should be path concat (try to find the command) */
		}
		else
		{
			i = ft_tablen(process->argv);
			ar = (char**)ft_tabmalloc(i + 2);
			size_t e = 0;
			while (e < i)
			{
				ar[e] = process->argv[e];
				++e;
			}
			ar[e] = token->symbol;
			process->argv = ar;
		}
	}
	job->first_process = process;
	execute_jobs(job);
	/* End of test part */
	return (e_success);
}
