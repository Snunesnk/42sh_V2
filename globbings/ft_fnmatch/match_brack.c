/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_brack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:25:28 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:29:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_fnmatch.h"
#include "g_char_classes.h"
#include "ft_fnmatch_internal.h"

static t_char_class_fct	valid_char_class(const char **cur)
{
	t_char_class_fct	f;
	size_t				len;
	const char			*ptr;

	len = 0;
	ptr = *cur + 2;
	while (*ptr && *ptr != ':')
	{
		++ptr;
		++len;
	}
	if (*ptr != ':' || *(ptr + 1) != ']')
		return (NULL);
	f = get_char_class_fct(*cur + 2, len);
	*cur = f ? ptr + 1 : *cur;
	return (f);
}

static int				exec_match(const char **cur, char string, int skip)
{
	t_char_class_fct	f;
	char				cur_char;
	const char			*next_char;

	if ((*cur)[1] == '-' && (*cur)[2] != ']')
	{
		next_char = (*cur)[2] != '\\' || skip < 0 ?
			*cur + 2 : *cur + 3;
		cur_char = **cur;
		*cur = *next_char ? next_char : next_char - 1;
		return (string >= cur_char && string <= *next_char);
	}
	else if (**cur == '[' && skip != 1 && (*cur)[1] == ':'
		&& (f = valid_char_class(cur)))
		return (f(string));
	return (**cur == string);
}

int						match_brack(const char **pattern, const char **string, \
				t_flags *flags)
{
	const char	*cur;
	const char	*not;
	int			skip;
	int			match;

	cur = *pattern + 1;
	not = *cur == '!' ? cur++ : *pattern;
	if (explicit_match(**string, flags) || !**string)
		return (0);
	match = 0;
	skip = flags->cur & FT_FNM_NOESCAPE ? -1 : 0;
	while (*cur && (*cur != ']' || skip > 0 || cur == not + 1))
	{
		if (skip || !(skip = *cur == '\\'))
		{
			match |= exec_match(&cur, **string, skip);
			skip = skip > 0 ? 0 : skip;
		}
		++cur;
	}
	if (!*cur)
		return (match_reg(pattern, string));
	*string = **string ? *string + 1 : *string;
	*pattern = *cur ? cur + 1 : cur;
	return (*not == '!' ? !match : match);
}
