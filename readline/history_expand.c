/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:26:29 by snunes            #+#    #+#             */
/*   Updated: 2020/03/03 19:00:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	g_hist_word_delim[] = " \t\n;&()|<>";
static int	g_pattern_length;

int		check_end_bracket(char *tmp)
{
	int	i;

	i = 0;
	while (!ft_isspace(tmp[i]) && tmp[i])
	{
		if (tmp[i] == ']')
			return (1);
		i++;
	}
	return (0);
}

char	*hist_expanse(char *value)
{
	char	*tmp;
	char	*hist_entry;

	tmp = value;
	hist_entry = value;
	while (*tmp && value && (tmp = ft_strchr(tmp, '!')))
	{
		if (check_end_bracket(tmp))
		{
			tmp = ft_strchr(tmp, ']');
			continue ;
		}
		g_pattern_length = 0;
		tmp++;
		if (ft_strchr(g_hist_word_delim, *tmp))
			continue ;
		if (!(hist_entry = get_hist_entry(tmp)))
			break ;
		value = replace_hist_exp(value, hist_entry);
		tmp = value;
	}
	if (!hist_entry || !value)
	{
		g_hist->nb_line = g_hist->total_lines;
		g_hist->offset = g_hist->used -1;
		free(value);
		return (NULL);
	}
	else if (g_pattern_length)
		ft_printf("\n%s\n", value);
	return (value);
}

char	*get_hist_entry(char *tmp)
{
	char	*hist_entry;
	int		sign;
	int		start;
	int		save;

	sign = 0;
	if (tmp[g_pattern_length] == '!')
		return (prev_hist());
	if (tmp[g_pattern_length] == '-')
	{
		sign = -1;
		g_pattern_length++;
	}
	start = g_pattern_length;
	while (!ft_strchr(g_hist_word_delim, tmp[g_pattern_length]))
		g_pattern_length++;
	save = tmp[g_pattern_length];
	tmp[g_pattern_length] = '\0';
	hist_entry = (ft_isdigit(tmp[start])) ? expand_num(tmp, start, sign) : \
				 expand_word(tmp, start, sign);
	tmp[g_pattern_length] = save;
	return (hist_entry);
}

char	*expand_num(char *value, int start, int sign)
{
	char	*hist_entry;
	int		entry;

	hist_entry = NULL;
	entry = ft_atoi(value + start);
	if (sign < 0)
		entry = g_hist->nb_line - entry;
	if (entry > g_hist->total_lines || entry <= 0 || g_hist->total_lines <= 1)
	{
		ft_dprintf(STDERR_FILENO, "\n./21sh: !%s: event not found\n", value);
		return (NULL);
	}
	while (entry > g_hist->nb_line)
		hist_entry = next_hist();
	while (entry < g_hist->nb_line)
		hist_entry = prev_hist();
	return (hist_entry);
}

char	*expand_word(char *value, int start, int sign)
{
	char	*hist_entry;

	(void)start;
	hist_entry = NULL;
	if (sign < 0)
		value++;
	while (g_hist->nb_line && ft_strncmp(value, g_hist->history_content + \
				g_hist->offset + 1, g_pattern_length + sign))
		hist_entry = prev_hist();
	if (ft_strncmp(value, g_hist->history_content + g_hist->offset + 1, \
				g_pattern_length + sign))
	{
		ft_dprintf(STDERR_FILENO, "\n./21sh: !%s: event not found\n", value);
		return (NULL);
	}
	return (hist_entry);
}

char	*replace_hist_exp(char *value, char *hist_entry)
{
	char	*new_value;
	int		size;
	int		i;

	if (g_pattern_length == 0)
		g_pattern_length += 1;
	i = 0;
	while (value[i] && (value[i] != '!' || ft_strchr(g_hist_word_delim, \
				value[i + 1])))
		i++;
	size = ft_strlen(value) - g_pattern_length + ft_strlen(hist_entry);
	if (!(new_value = (char *)ft_memalloc(sizeof(char) * (size + 2))))
	{
		ft_printf("\n./21sh: cannot allocate memory\n");
		return (NULL);
	}
	value[i] = '\0';
	ft_strcpy(new_value, value);
	ft_strcpy(new_value + i, hist_entry);
	ft_strcpy(new_value + i + ft_strlen(hist_entry), value + i \
			+ g_pattern_length + 1);
	free(value);
	g_hist->offset = g_hist->used - 1;
	g_hist->nb_line = g_hist->total_lines;
	return (new_value);
}
