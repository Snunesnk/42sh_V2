#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "ft_errno.h"
#include "ft_queue.h"
#include "error.h"
#include "tokens.h"
#include "grammar.h"

#include "job.h"

void	display_tokens(t_token *token)
{
	ft_printf("symbol: %s\n", token->symbol);/* deebug */
	ft_printf("type: %d\n\n", token->type);/* deebug */
}

int	parser(struct s_queue *queue)
{
	t_token	*token;

	queue_apply_to_each(queue, display_tokens); /* Verify tokens */

	/* This part should not be in parser, just for test during the building */
	extern char **environ;
	while ((token = queue_dequeue(queue, free))) /* not right free function for tokens */
	{
/*		*arg = token->symbol;
		job(arg, environ);
*/	}
	return (e_success);
}
