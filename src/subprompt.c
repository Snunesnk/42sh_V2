/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:28:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 16:17:37 by abarthel         ###   ########.fr       */
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
	tmp = get_input_fd(fd, qmode, "> ");
	while (tmp && ft_strcmp(eof, tmp) && !g_input_break)
	{
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = ft_strjoin(hereword, line);
		free(hereword);
		free(line);
		hereword = tmp;
		tmp = get_input_fd(fd, qmode, "> ");
		if (!tmp && !g_shell_is_interactive)
			g_eof = 1;
	}
	if (g_input_break && !g_eof)
	{
		free(tmp);
		free(hereword);
		return (NULL);
	}
	if (!tmp && g_shell_is_interactive)
	{
		free(hereword);
		return (NULL);
	}
	free(tmp);
	return (hereword);
}

static inline int	reset_return(int err)
{
	g_eof = 0;
	g_input_break = 0;
	g_subprompt = 0;
	return (err);
}

int		subprompt(int fd, t_list **lst, int qmode)
{ /* FULL_QUOTE: parser input claim, BSQUOTE: heredoc */
	char	*input;
	char	*tmp;

	g_subprompt = 1;
	if (qmode == BSQUOTE)
	{
		input = heredoc(fd, ((t_token*)((*lst)->next->content))->value, qmode);
		free(((t_token*)((*lst)->next->content))->value);
		((t_token*)((*lst)->next->content))->value = input;
		if (g_eof)
			return (reset_return(e_heredoc_warning));
		else if (g_input_break)
			return (reset_return(e_unexpected_eof_130));
		return (reset_return(e_success));
	}
	else if (qmode == FULL_QUOTE)
	{
		input = get_input_fd(fd, qmode, "> ");
		if (g_eof || !input)
		{
			psherror(e_unexpected_eof_2, NULL ,e_invalid_type);
			free(input);
			exit_clean(g_errordesc[e_unexpected_eof_2].code);
		}
		if (g_input_break)
			return (reset_return(e_unexpected_eof_130));
		tmp = ft_strjoin(input, "\n");
		free(input);
		input = tmp;
		*lst = lexer(input);
		free(input);
		return (reset_return(e_success));
	}
	return (reset_return(e_success));
}
