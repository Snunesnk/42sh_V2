#include "shell.h"

# define ASTERROR 125

int	execute_pipeline(t_ast *node, int foreground)
{
	return (execute_job(node->content, foreground));
}

int	execute_semi(t_ast *node, int foreground)
{
	if (node->left)
		execute_node(node->left, foreground);
	if (node->right)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_subshell(t_ast *node, int foreground)
{ /* Here is the idea */
	if (fork() == 0) /* get the pid and add it to the first_job list */
		exit(execute_node(node, foreground));
	else
	{
		/* Put job in foreground or background or non interactive */
		return (0);
	}
}

int	execute_and(t_ast *node, int foreground)
{
	/* Fork, get the pid to put it in job list and then pursue execute_node in the fork itself */
	/* Launch a subshell with node->left */
	if (node->left)
		execute_subshell(node->left, 0); /*  Get the PID and add it to the list in case fg and ctrl + c */
	if (node->right)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_andand(t_ast *node, int foreground)
{
	if (!execute_node(node->left, foreground))
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_or(t_ast *node, int foreground)
{
	if (execute_node(node->left, foreground))
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_while(t_ast *node, int foreground)
{
	int	ret;

	ret = 1;
	while (!execute_node(node->left, foreground))
		ret = execute_node(node->right, foreground);
	return (ret);
}

/*
int	execute_if(t_ast *node)
{
	if (!execute_node(node->left))
		return (execute_node(node->right));
}
*/

int	execute_node(t_ast *node, int foreground)
{
	if (node->type == NONE)
		return (execute_pipeline(node, foreground));
	else if (node->type == SEMI)
		return (execute_semi(node, foreground));
	else if (node->type == AND)
		return (execute_and(node, foreground));
	else if (node->type == AND_IF)
		return (execute_andand(node, foreground));
	else if (node->type == OR_IF)
		return (execute_or(node, foreground));
	else if (node->type == WHILE_WORD)
		return (execute_while(node, foreground));
/*	else if (node->type == IF)
		return (execute_if(node));
*/
	return (ASTERROR);
}
