/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:35:10 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 12:50:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_to_commandline(char **line, char *cmd)
{
	char	*tmp;

	if (!*line)
		*line = ft_strdup(cmd);
	else
	{
		tmp = ft_strnjoin(3, *line, " ", cmd);
		ft_memdel((void**)line);
		*line = tmp;
	}
}

static void	add_node_to_cmd(t_ast *node, char **command)
{
	char	*n;
	t_list	*lst;
	t_token	*tk;

	if (!node)
		return ;
	if (node->type == IO_NB || node->type == WORD)
	{
		lst = node->content;
		tk = lst->content;
		n = tk->value;
	}
	else
		n = g_tokval[node->type];
	add_to_commandline(command, n);
//	ft_printf("====> %s  <===\n ", n); // DEBUGG
}

static void	next_job_command(t_ast *ast, char **command)
{
	if (ast)
	{
		if (ast->left)
			next_job_command(ast->left, command);
		add_node_to_cmd(ast, command);
		if (ast->right)
			next_job_command(ast->right, command);
	}
}

void	get_job_command(t_ast *ast, char **command)
{
	char *tmp;

	if (ast)
	{
		next_job_command(ast, command);
		tmp = ft_strnjoin(3, *command, " ", "&");
		ft_memdel((void**)command);
		*command = tmp;
	}
}
