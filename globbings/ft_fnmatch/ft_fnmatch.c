/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:43:57 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/10 13:26:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fnmatch.h"
#include "ft_fnmatch_internal.h"

int		set_flags(char pattern, char string, t_flags *flags)
{
	flags->cur &= FT_FNM_EXTMASK;
	if (flags->next)
	{
		flags->cur |= flags->next;
		flags->next = 0;
	}
	if (pattern == '\\' && !(flags->cur & FT_FNM_NOESCAPE)
		&& !(flags->cur & FT_IFNM_FORCE_REG))
	{
		flags->next = FT_IFNM_FORCE_REG;
		flags->cur |= FT_IFNM_SKIP;
	}
	else if (string == '/' && (flags->cur & FT_FNM_PATHNAME)
		&& (flags->cur & FT_FNM_PERIOD))
		flags->next = FT_IFNM_LEADING_PERIOD;
	return (flags->cur);
}

int		ft_fnmatch_internal(const char *pattern, const char *string, \
			t_flags flags)
{
	int	match;

	match = 1;
	while (*pattern && match > 0)
	{
		if (set_flags(*pattern, *string, &flags) & FT_IFNM_SKIP)
			match = *++pattern ? match : 0;
		else if ((flags.cur & FT_IFNM_FORCE_REG))
			match = match_reg(&pattern, &string);
		else if (*pattern == '?')
			match = match_qmark(&pattern, &string, &flags);
		else if (*pattern == '[')
			match = match_brack(&pattern, &string, &flags);
		else if (*pattern == '*')
			match = match_star(&pattern, &string, &flags);
		else
			match = match_reg(&pattern, &string);
	}
	return (match < 0 ? match : *pattern || *string || !match);
}

int		ft_fnmatch(const char *pattern, const char *string, int flags)
{
	t_flags	f;

	f.next = 0;
	f.cur = flags;
	set_flags(0, '/', &f);
	if (ft_fnmatch_internal(pattern, string, f))
		return (FT_FNM_NOMATCH);
	return (0);
}
