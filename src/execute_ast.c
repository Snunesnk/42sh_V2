#include "shell.h"

# define ASTERROR 125

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
	return (ASTERROR);
}

int	execute_and(t_ast *node)
{
	/* fork, get the pid to put it in job list and then pursue execute_node in the fork itself */
	/* launch a subshell with node->left
	if (node->left)
		execute_subshell(node->left);  Get the PID and add it to the list in case fg and ctrl + c */
	if (node->right)
		return (execute_node(node->right));
	return (ASTERROR);
}

int	execute_andand(t_ast *node)
{
	if (!execute_node(node->left))
		return (execute_node(node->right));
	return (ASTERROR);
}

int	execute_or(t_ast *node)
{
	if (execute_node(node->left))
		return (execute_node(node->right));
	return (ASTERROR);
}

int	execute_while(t_ast *node)
{
	int	ret;

	ret = 1;
	while (!execute_node(node->left))
		ret = execute_node(node->right);
	return (ret);
}

/*
int	execute_if(t_ast *node)
{
	if (!execute_node(node->left))
		return (execute_node(node->right));
}
*/

int	execute_node(t_ast *node)
{
	if (node->type == NONE)
		return (execute_pipeline(node));
	else if (node->type == SEMI)
		return (execute_semi(node));
	else if (node->type == AND)
		return (execute_and(node));
	else if (node->type == AND_IF)
		return (execute_andand(node));
	else if (node->type == OR_IF)
		return (execute_or(node));
	else if (node->type == WHILE_WORD)
		return (execute_while(node));
/*	else if (node->type == IF)
		return (execute_if(node));
*/
	return (ASTERROR);
}
