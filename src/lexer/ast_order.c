#include "libft.h"
#include "shell.h"

/*static t_ast	*astnew(t_list *lst, uint64_t type)
{
	t_ast	*ast;

	ast = (t_ast*)malloc(sizeof(t_ast));
	if (ast != NULL)
	{
		ft_bzero(ast, sizeof(t_ast));
		ast->type = type;
		ast->content = lst;
	}
	return (ast);
}*/

static void	node_rot(t_ast **ast, t_ast *prev_node, t_ast **head)
{
	t_ast	*tmp;

	if (prev_node == NULL)
	{
		tmp = (*ast)->right;
		(*head)->right = ((t_ast*)(tmp))->left;
		((t_ast*)(tmp))->left = (*head);
		(*head) = tmp;
	}
	else
	{
		tmp = *ast;
		prev_node->right = (*ast)->right;
		tmp->right = ((t_ast*)(prev_node->right))->left;
		((t_ast*)(prev_node->right))->left = tmp;
	}
}

void		ast_order(t_ast **ast)
{
	t_ast	*head;
	t_ast	*prev_node;

	head = *ast;
	prev_node = NULL;
	if (*ast != NULL)
	{
		while ((*ast)->right)
		{
			if ((*ast)->type == AND_IF || (*ast)->type == OR_IF)
			{
				if (((t_ast*)((*ast)->right))->type == AND)
				{
					node_rot(ast, prev_node, &head);
					*ast = head;
					prev_node = NULL;
				}
				else
				{
					prev_node = *ast;
					*ast = (*ast)->right;
				}
			}
			else
			{
				prev_node = *ast;
				*ast = (*ast)->right;
			}
		}
	}
	*ast = head;
}
