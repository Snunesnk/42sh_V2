#include "shell.h"

static void	print_ast(int fd, t_ast *node)
{
	char	*n;
	char	*side;
	t_list	*lst;
	t_token *tk;

	if (node)
	{
		print_ast(fd, node->left);
		if (node->type == IO_NB || node->type == WORD)
		{
			lst = node->content;
			tk = lst->content;
			n = tk->value;
		}
		else
			n = token_tab[node->type];
		ft_dprintf(fd, "\"%s %p\";\n", n, n);
		if (node->left)
		{
			if (node->left->type == IO_NB || node->left->type == WORD)
			{
				lst = node->left->content;
				tk = lst->content;
				side = tk->value;
			}
			else
				side = token_tab[node->left->type];
			ft_dprintf(fd, "\"%s %p\" -> \"%s %p\";\n", n, n, side, side);
		}
		print_ast(fd, node->right);
		if (node->right)
		{
			if (node->right->type == IO_NB || node->right->type == WORD)
			{
				lst = node->right->content;
				tk = lst->content;
				side = tk->value;
			}
			else
				side = token_tab[node->right->type];
			ft_dprintf(fd, "\"%s %p\" -> \"%s %p\";\n", n, n, side, side);
		}
	}
}

void		graph_ast(t_ast *ast)
{
	int fd;

	fd = open("graph.dot", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_dprintf(fd, "digraph finite_state_machine {\nsize=\"8\";\nrankdir=TB;\n");
	print_ast(fd, ast);
	ft_dprintf(fd, "\n}\n");
	close(fd);
}
