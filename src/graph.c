/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:50:47 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 19:16:31 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*tok_str(t_ast *node)
{
	char	*n;
	t_list	*lst;
	t_token *tk;

	if (node->type == IO_NB || node->type == WORD)
	{
		lst = node->content;
		tk = lst->content;
		n = tk->value;
	}
	else
		n = g_token_tab[node->type];
	return (n);
}

static void	print_ast(int fd, t_ast *node)
{
	char	*n;

	if (node)
	{
		print_ast(fd, node->left);
		n = tok_str(node);
		ft_dprintf(fd, "%lu [label=\"%s\"];\n",
				(long unsigned)node, n);
		if (node->left)
		{
			ft_dprintf(fd, "%lu -- %lu;\n",
				(long unsigned)node, (long unsigned)node->left);
		}
		print_ast(fd, node->right);
		if (node->right)
		{
			ft_dprintf(fd, "%lu -- %lu;\n",
				(long unsigned)node, (long unsigned)node->right);
		}
	}
}

void		graph_ast(t_ast *ast)
{
	int fd;

	fd = open("tools/graph.dot", O_CREAT | O_TRUNC | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_dprintf(fd, "strict graph {\nsize=\"8\";\nrankdir=TB;\n");
	print_ast(fd, ast);
	ft_dprintf(fd, "\n}\n");
	close(fd);
}
