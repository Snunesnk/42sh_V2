/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:28:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 18:01:59 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

int	g_oneline = 0;

static char	*free_loop(char *here, char *tmp)
{
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

static char	*get_heredoc_input(int fd, char *eof, char *here)
{
	char *tmp;
	char *line;

	tmp = NULL;
	line = NULL;
	g_subprompt = 1;
	tmp = get_input_fd(fd, BSQUOTE, "> ");
	if (g_oneline)
		return (tmp);
	while (tmp && ft_strcmp(eof, tmp) && !g_input_break)
	{
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = ft_strjoin(here, line);
		free(here);
		free(line);
		here = tmp;
		tmp = get_input_fd(fd, BSQUOTE, "> ");
	}
	g_subprompt = 0;
	return (free_loop(here, tmp));
}

t_list		*subprompt(int fd)
{
	t_list	*lst;
	char	*input;
	char	*tmp;

	g_oneline = 1;
	input = get_heredoc_input(fd, NULL, NULL);
	tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;
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

int			heredoc(int fd, t_list *lst)
{
	char	*eof;
	char	*input;

	eof = ((t_token*)(lst->next->content))->value;
	input = get_heredoc_input(fd, eof, ft_strdup(""));
	if (!input && !g_input_break)
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
	((t_token*)(lst->next->content))->value = input;
	return (e_success);
}
