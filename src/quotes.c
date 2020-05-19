/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:28:32 by snunes            #+#    #+#             */
/*   Updated: 2020/05/15 12:37:44 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "quotes.h"

int		get_qmode(int qmode, char c)
{
	if (c && (qmode & BSQUOTE))
		return (qmode & ~BSQUOTE);
	else if (c == '\\' && qmode != SQUOTE)
		return (qmode | BSQUOTE);
	else if (c == '"' && qmode != SQUOTE)
		return (qmode == DQUOTE ? NO_QUOTE : DQUOTE);
	else if (c == '\'' && qmode != DQUOTE)
		return (qmode == SQUOTE ? NO_QUOTE : SQUOTE);
	return (qmode);
}

char	*ft_strstr_qmode(const char *str, const char *to_find,
			int allowed_qmodes, int *qmode)
{
	int			l;
	const char	*needle;

	l = ft_strlen(to_find);
	while (*str && *to_find)
	{
		needle = to_find;
		while (*str && *needle && *str == *needle)
		{
			++str;
			++needle;
		}
		if (!*needle && !(*qmode & ~allowed_qmodes))
			return ((char *)str - l);
		str -= needle - to_find;
		*qmode = get_qmode(*qmode, *str++);
	}
	return (l ? 0 : (char *)str);
}

int		rm_quotes(char **str, int old_qmode)
{
	char	*dup;
	char	*pdup;
	char	*pstr;
	int		qmode;

	pstr = *str;
	dup = NULL;
	pdup = NULL;
	while (*pstr)
	{
		if ((qmode = get_qmode(old_qmode, *pstr)) != old_qmode && !dup)
		{
			if (!(dup = ft_strnew(ft_strlen(*str))))
				return (e_cannot_allocate_memory);
			pdup = ft_strncat(dup, *str, pstr - *str) + (pstr - *str);
		}
		else if (dup && (qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE)
			|| (qmode == (DQUOTE | BSQUOTE) && !ft_strchr("\\\"`'$", pstr[1]))))
			*pdup++ = *pstr;
		old_qmode = qmode;
		++pstr;
	}
	*str = dup ? ft_strcpy(*str, dup) : *str;
	free(dup);
	return (e_success);
}

int		has_unquoted_spec_chars(const char *str, const char *spec)
{
	int	qmode;

	qmode = NO_QUOTE;
	while (*str)
	{
		if ((qmode = get_qmode(qmode, *str)) == NO_QUOTE
			&& ft_strchr(spec, *str))
			return (1);
		++str;
	}
	return (0);
}
