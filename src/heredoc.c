/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:56:57 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/19 16:38:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

static char	*return_heredoc(char *tmp, char *hereword)
{
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

static int	get_heredoc_qmode(char **eof, int qmode)
{
	size_t	orig;

	orig = ft_strlen(*eof);
	rm_quotes(eof, NO_QUOTE);
	if (ft_strlen(*eof) == orig)
		return (qmode);
	return (NO_QUOTE);
}

char		*heredoc(int fd, char **eof, int qmode)
{
	char	*tmp;
	char	*hereword;
	char	*line;

	qmode = get_heredoc_qmode(eof, qmode);
	tmp = NULL;
	line = NULL;
	hereword = ft_strdup("");
	tmp = get_input_fd(fd, qmode, "> ");
	while (tmp && ft_strcmp(*eof, tmp) && !g_input_break)
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
	add_hentry(hereword, ft_strlen(hereword));
	if (qmode)
		expand_heredoc(&hereword);
	return (return_heredoc(tmp, hereword));
}
