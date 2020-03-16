#include "avl.h"

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node(node->left);
	free(node->name);
	if (node->right)
		free_node(node->right);
	free(node);
}

int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
