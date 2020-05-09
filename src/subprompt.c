/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:28:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 11:29:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	g_oneline = 0;

t_list		*subprompt(void)
{
	t_list	*lst;
	char	*input;

	g_oneline = 1;
	input = get_heredoc_input(NULL, NULL, NULL, NULL);
	g_oneline = 0;
	g_subprompt = 0;
	if (g_input_break)
	{
		g_input_break = 0;
		return (NULL);
	}
	g_input_break = 0;
	lst = lexer(input);
	free(input);
	return (lst);
}

static void	loop_heredoc(char **eof, char **here, char **tmp, char **line)
{
	while (*tmp && ft_strcmp(*eof, *tmp) && !g_input_break)
	{
		*line = ft_strjoin(*tmp, "\n");
		free(*tmp);
		*tmp = ft_strjoin(*here, *line);
		free(*here);
		free(*line);
		*here = *tmp;
		*tmp = get_input("> ", 0);
	}
	g_subprompt = 0;
}

char		*get_heredoc_input(char *eof, char *here, char *tmp, char *line)
{
	g_subprompt = 1;
	tmp = get_input("> ", 0);
	if (g_oneline)
		return (tmp);
	loop_heredoc(&eof, &here, &tmp, &line);
	if (g_input_break && !g_eof)
	{
		free(tmp);
		free(here);
		return (NULL);
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
		if (!heredoc && !g_input_break)
			return (e_syntax_error);
		else if (g_input_break && !g_eof)
		{
			g_input_break = 0;
			g_eof = 0;
			return (e_invalid_input);
		}
		g_input_break = 0;
		g_eof = 0;
		free(eof);
		((t_token*)(lst->next->content))->value = heredoc;
	}
	return (e_success);
}
