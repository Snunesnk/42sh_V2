/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:56:57 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/19 15:58:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "quotes.h"

int			rm_heredoc_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\\' && str[1])
			str = (char *)ft_memmove((void *)str,
				(void *)str + 1, ft_strlen(str + 1) + 1);
		++str;	
	}
	return (0);
}

static int	expand_heredoc(char **hereword)
{
	int		ret;
	char	*tmp;

	if (!(tmp = ft_escape_spec(*hereword, "'\"")))
		return (e_cannot_allocate_memory);
	free(*hereword);
	*hereword = tmp;
	ret = treat_single_exp(hereword, 0, NULL);
	ret = !ret ? rm_heredoc_quotes(*hereword) : ret;
	return (ret);
}

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
