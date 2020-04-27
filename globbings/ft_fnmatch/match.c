/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:26:00 by snunes            #+#    #+#             */
/*   Updated: 2020/04/27 12:04:27 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_fnmatch.h"
#include "ft_fnmatch_internal.h"

int		explicit_match(char string, t_flags *flags)
{
	return ((string == '/' && (flags->cur & FT_FNM_PATHNAME))
		|| (string == '.' && (flags->cur & FT_IFNM_LEADING_PERIOD)));
}

int		match_qmark(const char **pattern, const char **string,
			t_flags *flags)
{
	int	match;

	match = !!**string && !explicit_match(**string, flags);
	*pattern = *pattern + 1;
	*string = **string ? *string + 1 : *string;
	return (match);
}

int		match_reg(const char **pattern, const char **string)
{
	int	match;

	match = **pattern == **string;
	*pattern = *pattern + 1;
	*string = **string ? *string + 1 : *string;
	return (match);
}

int		match_star(const char **pattern, const char **string,
				t_flags *flags)
{
	int		match;

	match = 1;
	while ((*pattern)[1] == '*')
		++(*pattern);
	if (explicit_match(**string, flags))
		return (*++(*pattern) && match_reg(pattern, string));
	match = ft_fnmatch_internal(*pattern + 1, *string, *flags);
	if (match > 0 && **string)
		match = ft_fnmatch_internal(*pattern, *string + 1, *flags);
	if (match > 0 && !**string)
		match = -1;
	*string = ft_strchr(*string, 0);
	*pattern = ft_strchr(*pattern, 0);
	return (match < 0 ? match : !match);
}
