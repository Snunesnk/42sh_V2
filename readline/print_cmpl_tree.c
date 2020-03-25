#include "ft_readline.h"

void	print_tree(t_node *compl_tree)
{
	if (!compl_tree)
		return ;
	if (compl_tree->left)
		print_tree(compl_tree->left);
	ft_printf("%s\n", compl_tree->name);
	if (compl_tree->right)
		print_tree(compl_tree->right);
}
