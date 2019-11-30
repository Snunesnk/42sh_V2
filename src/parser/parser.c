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

/*
int	execute_tree()
{
	argv = (char**)ft_memalloc(sizeof(char*) * 2);
	*argv = token->symbol;
	job(argv, environ);
	return (0);
} */

int	build_tree(t_node **root, t_token *token)
{
	(void)root;
	(void)token;
	return (0);
}

int	parser(struct s_queue *queue)
{
	t_node	*tree;
	t_token	*token;
/*	char	**argv;
*/
	queue_apply_to_each(queue, display_tokens); /* Verify tokens */

	/* This part should not be in parser, just for test during the building */
/*	extern char **environ;
*/	while ((token = queue_dequeue(queue, NULL))) /* not right free function for tokens */
	{
		build_tree(&tree, token);
	}
	/* End of test part */
	return (e_success);
}
