/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 22:37:05 by snunes            #+#    #+#             */
/*   Updated: 2020/05/10 21:53:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

char		*get_beg_matching_hist(char **line, char *pattern)
{
	char	*tmp;
	int		pat_len;

	tmp = *line;
	if (!tmp)
		return (tmp);
	if (!pattern)
		return (prev_hist());
	pat_len = ft_strlen(pattern);
	while (!ft_strnequ(tmp, pattern, pat_len) && g_hist.nb_line > 1)
		tmp = prev_hist();
	if (ft_strnequ(tmp, pattern, pat_len))
		*line = tmp;
	else
	{
		while (!ft_strnequ(tmp, *line, pat_len) \
				&& g_hist.nb_line <= g_hist.total_lines)
			tmp = next_hist();
		*line = tmp;
		tmp = NULL;
	}
	return (tmp);
}

char		*get_matching_hist(char **line, char *patern)
{
	char	*tmp;
	int		ret;

	ret = g_hist.nb_line;
	tmp = *line;
	if (!tmp)
		return (tmp);
	while (!ft_strstr(tmp, patern) && g_hist.nb_line > 1)
		tmp = prev_hist();
	if (ft_strstr(tmp, patern))
		*line = tmp;
	else
	{
		while (g_hist.nb_line < ret)
			tmp = next_hist();
		*line = tmp;
		tmp = NULL;
	}
	return (tmp);
}

int			test_c_value(union u_buffer c)
{
	if ((ft_isprint(c.value) && c.value != 9) || c.value == 127)
		return (0);
	if (enter_rc(c))
		return (1);
	if (isctrlkey(c))
		return (1);
	if (ismetachar(c))
		return (1);
	if (isstdkey(c.value))
		return (1);
	return (0);
}

void		history_up(void)
{
	char *s;

	if (!g_hist.total_lines)
		return ;
	if (g_hist.nb_line == g_hist.total_lines + 1)
	{
		if (g_original_cmd)
		{
			free(g_original_cmd);
			g_original_cmd = NULL;
		}
		if (!(g_original_cmd = ft_strdup(g_line.line)))
		{
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
			return ;
		}
	}
	clear_line();
	s = prev_hist();
	if (!*s && g_original_cmd)
		insert_text(g_original_cmd, ft_strlen(g_original_cmd));
	else
		insert_text(s, ft_strlen(s));
}

void		history_down(void)
{
	char	*s;

	if (!g_hist.total_lines || g_hist.nb_line > g_hist.total_lines)
		return ;
	s = NULL;
	clear_line();
	s = next_hist();
	if (!*s && g_original_cmd)
		insert_text(g_original_cmd, ft_strlen(g_original_cmd));
	else
		insert_text(s, ft_strlen(s));
}
