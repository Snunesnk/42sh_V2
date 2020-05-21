/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 22:57:14 by snunes            #+#    #+#             */
/*   Updated: 2020/05/21 11:09:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "ft_readline.h"

/*

TODO: check if this is really useful

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

*/

char	*do_hist_exp(char **value, char *hist_entry)
{
	char	*tmp;
	int		qmode;

	tmp = *value;
	qmode = NO_QUOTE;
	while (*tmp && *value
		&& (tmp = ft_strstr_qmode(tmp, "!", NO_QUOTE, &qmode)))
	{
		if (tmp > *value && *(tmp - 1) == '[')
		{
			tmp++;
			continue ;
		}
		g_pattern_length = 0;
		tmp++;
		if (ft_strchr(g_hist_word_delim, *tmp))
			continue ;
		if (!(hist_entry = get_hist_entry(tmp)))
			break ;
		*value = replace_hist_exp(*value, hist_entry, tmp - 1 - *value);
		tmp = *value;
	}
	return (hist_entry);
}
