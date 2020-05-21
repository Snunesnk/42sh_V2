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

char	*do_hist_exp(char **value, char *hist_entry)
{
	char	*tmp;
	int		qmode;

	tmp = *value;
	qmode = NO_QUOTE;
	while (*tmp && *value)
	{
		if (*tmp == '!' && qmode == NO_QUOTE)
		{
			g_pattern_length = 0;
			++tmp;
			if (ft_strchr(g_hist_word_delim, *tmp))
				continue ;
			if (!(hist_entry = get_hist_entry(tmp)))
				break ;
			*value = replace_hist_exp(*value, hist_entry, tmp - 1 - *value);
			tmp = *value;
			qmode = NO_QUOTE;
		}
		if (*tmp == '[' && tmp[1] == '!'
			&& qmode == NO_QUOTE && ft_strchr(tmp, ']'))
			++tmp;
		qmode = get_qmode(qmode, *tmp);
		++tmp;
	}
	return (hist_entry);
}
