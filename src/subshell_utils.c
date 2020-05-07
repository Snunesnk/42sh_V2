/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:35:10 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 12:31:38 by abarthel         ###   ########.fr       */
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
		n = token_tab[node->type];
	add_to_commandline(command, n);
//	ft_printf("====> %s  <===\n ", n); // DEBUGG
}

void	get_job_command(t_ast *ast, char **command)
{
	if (ast)
	{
		if (ast->left)
			get_job_command(ast->left, command);
		add_node_to_cmd(ast, command);
		if (ast->right)
			get_job_command(ast->right, command);
	}
}
