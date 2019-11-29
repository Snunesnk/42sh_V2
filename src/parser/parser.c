#include <stdlib.h>

#include "libft.h"
#include "ft_errno.h"
#include "ft_queue.h"
#include "error.h"
#include "tokens.h"

void	display_tokens(t_token *token)
{
	ft_printf("symbol: %s\n", token->symbol);/* deebug */
	ft_printf("type: %d\n\n", token->type);/* deebug */
}

int	parser(struct s_queue *queue)
{
	queue_apply_to_each(queue, display_tokens);
	return (e_success);
}
