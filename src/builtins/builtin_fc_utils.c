/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:22:01 by snunes            #+#    #+#             */
/*   Updated: 2020/03/09 20:15:33 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		free_substitute(t_sub *substitute)
{
	t_sub	*tmp;

	while (substitute)
	{
		tmp = substitute->next;
		free(substitute->pat);
		free(substitute->rep);
		free(substitute);
		substitute = tmp;
	}
}

void		fc_replace_last_hist(char *tmp)
{
	unsigned int	i;

	g_hist->offset = g_hist->used - 1;
	prev_hist();
	i = g_hist->offset;
	while (i < g_hist->used - 1)
	{
		g_hist->history_content[i] = '\0';
		i++;
	}
	g_hist->used = g_hist->offset + 1;
	g_hist->total_lines -= 1;
	if (tmp)
		add_hentry(tmp, 1);
}

char		*ft_strreplace(char **str, char *pattern, char *replacement)
{
	char	*tmp;
	int		nb_occur;
	int		pat_len;
	int		rep_len;
	int		str_len;

	tmp = *str;
	nb_occur = 0;
	pat_len = (int)ft_strlen(pattern);
	rep_len = (int)ft_strlen(replacement);
	str_len = (int)ft_strlen(*str);
	while ((tmp = ft_strstr(tmp, pattern)))
	{
		nb_occur++;
		tmp += pat_len;
	}
	if (pat_len < rep_len && !(*str = ft_memrealloc((void **)str, str_len, \
					str_len + ((rep_len - pat_len) * nb_occur) + 1)))
		return (NULL);
	tmp = *str;
	while ((tmp = ft_strstr(tmp, pattern)))
	{
		ft_memmove(tmp + rep_len, tmp + pat_len, ft_strlen(tmp) - pat_len + 1);
		ft_memmove(tmp, replacement, rep_len);
		tmp += rep_len;
	}
	return (*str);
}
