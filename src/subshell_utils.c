/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:35:10 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 12:07:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_to_commandline(char **line, char *cmd)
{
	char	*tmp;

	if (!*line)
		*line = cmd;
	else
	{
		tmp = ft_strnjoin(3, *line, " ", cmd);
		free(cmd);
		ft_memdel((void**)line);
		*line = tmp;
	}
}

static void	add_node_to_cmd(t_ast *node, char **command)
{
	char	*n;
	t_list	*lst;

	if (!node)
		return ;
	if (node->type == IO_NB || node->type == WORD)
	{
		lst = node->content;
		n = commandline(lst);
	}
	else
		n = ft_strdup(g_tokval[node->type]);
	add_to_commandline(command, n);
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

void		get_job_command(t_ast *ast, char **command)
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
