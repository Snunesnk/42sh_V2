/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 22:37:05 by snunes            #+#    #+#             */
/*   Updated: 2020/04/29 14:43:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

char		*get_beg_matching_hist(char **line, char *patern)
{
	char	*tmp;
	int		pat_len;

	tmp = *line;
	if (!tmp)
		return (tmp);
	if (!patern)
		return (prev_hist());
	pat_len = ft_strlen(patern);
	while (!ft_strnequ(tmp, patern, pat_len) && g_hist->nb_line > 0)
		tmp = prev_hist();
	if (ft_strnequ(tmp, patern, pat_len))
		*line = tmp;
	else
	{
		while (!ft_strnequ(tmp, *line, pat_len) \
				&& g_hist->nb_line < g_hist->total_lines)
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

	ret = g_hist->nb_line;
	tmp = *line;
	if (!tmp)
		return (tmp);
	while (!ft_strstr(tmp, patern) && g_hist->nb_line > 0)
		tmp = prev_hist();
	if (ft_strstr(tmp, patern))
		*line = tmp;
	else
	{
		while (g_hist->nb_line < ret)
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

	s = g_line.line;
	if (g_hist->offset == g_hist->used - 1)
	{
		if (g_original_cmd)
			free(g_original_cmd);
		if (!(g_original_cmd = ft_strdup(g_line.line)))
		{
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
			return ;
		}
	}
	s = prev_hist();
	clear_line();
	if (s)
		insert_text(s, ft_strlen(s));
	else if (g_original_cmd)
		insert_text(g_original_cmd, ft_strlen(s));
}

void		history_down(void)
{
	char *s;

	s = next_hist();
	clear_line();
	if (s && *s)
		insert_text(s, ft_strlen(s));
	else if (g_original_cmd)
		insert_text(g_original_cmd, ft_strlen(g_original_cmd));
}
