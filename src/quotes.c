/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:28:32 by snunes            #+#    #+#             */
/*   Updated: 2020/04/30 13:00:50 by yforeau          ###   ########.fr       */
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

char	*unquote_str(char *quoted_str)
{
	char	*cpy;
	int		i;
	int		qmode;
	int		old_qmode;

	if (!quoted_str || !(cpy = ft_strnew(ft_strlen(quoted_str))))
		return (NULL);
	i = 0;
	old_qmode = NO_QUOTE;
	while (*quoted_str)
	{
		qmode = get_qmode(old_qmode, *quoted_str);
		if (qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE))
			cpy[i++] = *quoted_str;
		++quoted_str;
	}
	cpy[i] = 0;
	return (cpy);
}

int		rm_quotes(char **str, int old_qmode)
{
	char	*dup;
	char	*pdup;
	char	*pstr;
	int		qmode;

	pstr = *str;
	dup = NULL;
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

int		get_str_qmode(int qmode, char *s)
{
	while (*s)
		qmode = get_qmode(qmode, *s++);
	return (qmode);
}
