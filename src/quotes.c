/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:28:32 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 14:39:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "quotes.h" //TEMP

/*
** Return 1 if index is without quotes or has \ before, i.e. inihibited
*/

/*
char	*move_to_next_inhibitor_boundary(char *s)
{
	char	backq;
	size_t	i;

	i = 0;
	baskq = 0;
	while (s[i] && i < index)
	{
		if (s[i] == '\'')
			backq ^= '\'';
	}
	return (backq);
}
*/

//TEMP: unquote aliases

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

char		*unquote_str(char *quoted_str)
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

int		rm_quotes(char **str)
{
	char	*dup;
	char	*pdup;
	char	*pstr;
	int		qmode;
	int		old_qmode;

	pstr = *str;
	dup = NULL;
	old_qmode = NO_QUOTE;
	while (*pstr)
	{
		if ((qmode = get_qmode(old_qmode, *pstr)) != old_qmode && !dup)
		{
			if (!(dup = ft_strnew(ft_strlen(*str))))
				return (e_cannot_allocate_memory);
			pdup = ft_strncat(dup, *str, pstr - *str) + (pstr - *str);
		}
		else if ((qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE)) && dup)
			*pdup++ = *pstr;
		old_qmode = qmode;
		++pstr;
	}
	*str = dup ? ft_strcpy(*str, dup) : *str;
	ft_memdel((void **)&dup);
	return (e_success);
}

//TEMP
