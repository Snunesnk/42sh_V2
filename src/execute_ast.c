#include "shell.h"

int	execute_pipeline(t_ast *node)
{
	return (launch_all_jobs(node->content));
}

int	execute_semi(t_ast *node)
{
	if (node->left)
		execute_node(node->left);
	if (node->right)
		return (execute_node(node->right));
}

int	execute_and(t_ast *node)
{
	/* launch a subshell with node->left */
	if (node->left)
		execute_subshell(node->left);
	if (node->right)
		return (execute_node(node->right));
}

int	execute_andand(t_ast *node)
{
	if (!execute_node(node->left))
		return (execute_node(node->right));
}

int	execute_or(t_ast *node)
{
	if (execute_node(node->left))
		return (execute_node(node->right));
}

int	execute_node(t_ast *node)
{
	if (node->type == NONE)
		return (execute_pipeline(node));
	else if (node->type == SEMI)
		return (execute_semi(node));
	else if (node->type == AND)
		return (execute_and(node));
	else if (node->type == ANDAND)
		return (execute_andand(node));
	else if (node->type == OR)
		return (execute_or(node));
}
