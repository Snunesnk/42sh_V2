/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 19:35:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/26 12:04:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char	*get_heredoc_input(char *eof, char *here, char *tmp, char *line)
{
	if (g_shell_is_interactive)
		tmp = ft_readline("> ");
	else
		get_stdin(&tmp);
	while (tmp && ft_strcmp(eof, tmp))
	{
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = ft_strjoin(here, line);
		free(here);
		free(line);
		here = tmp;
		if (g_shell_is_interactive)
			tmp = ft_readline("> ");
		else
			get_stdin(&tmp);
	}
	if (!tmp)
	{
		free(here);
		return (NULL);
	}
	free(tmp);
	return (here);
}

int			heredoc(t_list *lst, int curr, int next)
{
	char	*eof;
	char	*heredoc;

	if ((curr == DLESS || curr == DLESSDASH) && next == WORD)
	{
		eof = ((t_token*)(lst->next->content))->value;
		heredoc = get_heredoc_input(eof, ft_strdup(""), NULL, NULL);
		if (!heredoc)
			return (e_syntax_error);
		free(eof);
		((t_token*)(lst->next->content))->value = heredoc;
	}
	return (e_success);
}

t_ast		*alloc_node(int type, t_list *pipeline, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_memalloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->content = pipeline;
	node->left = left;
	node->right = right;
	return (node);
}
