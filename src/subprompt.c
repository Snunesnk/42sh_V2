/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:28:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 14:46:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

int	g_oneline = 0;

static char	*heredoc(int fd, char *eof, int qmode)
{
	char *tmp;
	char *hereword;
	char *line;

	tmp = NULL;
	line = NULL;
	hereword = ft_strdup("");
	g_subprompt = 1;
	tmp = get_input_fd(fd, qmode, "> ");
	if (g_oneline)
		return (tmp);
	while (tmp && ft_strcmp(eof, tmp) && !g_input_break)
	{
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = ft_strjoin(hereword, line);
		free(hereword);
		free(line);
		hereword = tmp;
		tmp = get_input_fd(fd, qmode, "> ");
	}
	g_subprompt = 0;
	if (g_input_break && !g_eof)
	{
		g_input_break = 0;
		free(tmp);
		free(hereword);
		return (NULL);
	}
	if (!tmp)
	{
		free(hereword);
		return (NULL);
	}
	free(tmp);
	return (hereword);
}

int		subprompt(int fd, t_list **lst, int qmode)
{ /* FULL_QUOTE: parser input claim, BSQUOTE: heredoc */
	char	*input;

	if (qmode == BSQUOTE)
	{
		input = heredoc(fd, ((t_token*)((*lst)->next->content))->value, qmode);
		free(((t_token*)((*lst)->next->content))->value);
		((t_token*)((*lst)->next->content))->value = input;
		if (g_eof)
		{
			g_eof = 0;
			g_input_break = 0;
			return (e_heredoc_warning);
		}
		g_input_break = 0;
		g_eof = 0;
		/* if: check all posible errors ctrl C, ctrl D, unexpected EOF, etc */
		return (e_success);
	}
/*	else if (qmode == FULL_QUOTE)
	{
		g_oneline = 1;
		input = get_input(fd, NULL, NULL);
		tmp = ft_strjoin(input, "\n");
		free(input);
		input = tmp;
		g_oneline = 0;
		g_subprompt = 0; // ??
	}
	if (!input && !g_input_break)
	{
		return (e_syntax_error);
	}
	else if (!input)
	{
		return (e_invalid_input);
	}
	else if (g_input_break && !g_eof)
	{
		g_input_break = 0;
		g_eof = 0;
		return (e_invalid_input);
	}
	else if (g_input_break)
	{
		g_input_break = 0;
		return (e_invalid_input);
	}
	g_input_break = 0;
	g_eof = 0;
	free(eof);
	if (BSQUOTE)
		((t_token*)((*lst)->next->content))->value = input;
	else if (FULL_QUOTE)
		*lst = lexer(input);
	free(input);
*/	return (e_success);
}
