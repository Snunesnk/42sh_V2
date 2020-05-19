/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:38:12 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/19 18:24:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"
#include "quotes.h"

static int	rm_quotes_heredoc(char *str, char *spec, int n)
{
	int	count;

	count = 0;
	while (*str && n)
	{
		if (*str == '\\' && str[1] && ft_strchr(spec, str[1]))
		{
			str = (char *)ft_memmove((void *)str,
				(void *)str + 1, ft_strlen(str + 1) + 1);
			n = n > 0 ? n - 1 : n;
			++count;
		}
		++str;
		n = n > 0 ? n - 1 : n;
	}
	return (count);
}

static int		replace_expansion_heredoc(char **token, char **next, int ref)
{
	size_t	lcontent;
	char	*new;
	size_t	lnew;
	size_t	lprefix;
	int		ret;

	lcontent = 0;
	ret = e_success;
	lprefix = (size_t)((*next) - (*token));
	if (!(ret = g_tags[ref].f(&lcontent, next,
	g_tags[ref].opentag, g_tags[ref].closetag)))
	{
		lcontent -= rm_quotes_heredoc(*next, SHELL_QUOTES, (int)lcontent);
		lnew = lprefix + ft_strlen(*next);
		new = (char*)ft_memalloc(sizeof(char) * (lnew + 1));
		ft_strncat(new, *token, lprefix);
		ft_memdel((void**)token);
		ft_strcat(new, *next);
		ft_memdel((void**)next);
		*next = &(new)[lcontent + lprefix];
		*token = new;
		return (e_success);
	}
	return (ret);
}

static char	*get_closest_exp_heredoc(char *str, int *ref, int *qmode)
{
	int		i;
	char	*ptr;
	char	*closest;
	int		tmp_qmode;
	int		orig_qmode;

	i = 0;
	*ref = -1;
	closest = NULL;
	orig_qmode = *qmode;
	while (*g_tags[i].opentag && *g_tags[i].opentag != '~')
	{
		tmp_qmode = orig_qmode;
		ptr = ft_strstr_qmode(str, g_tags[i].opentag,
			FULL_QUOTE & ~BSQUOTE, &tmp_qmode);
		if (ptr && (!closest || ptr < closest))
		{
			*qmode = tmp_qmode;
			closest = ptr;
			*ref = i;
		}
		++i;
	}
	return (closest);
}

static int	treat_single_exp_heredoc(char **str)
{
	int		ref;
	int		ret;
	int		qmode;
	char	*next;

	ret = e_success;
	next = *str;
	qmode = NO_QUOTE;
	while (!ret && (next = get_closest_exp_heredoc(next, &ref, &qmode)))
		ret = replace_expansion_heredoc(str, &next, ref);
	if (ret)
		psherror(ret, *str, e_cmd_type);
	return (ret);
}

int			expand_heredoc(char **hereword)
{
	int		ret;

	if (!(ret = treat_single_exp_heredoc(hereword)))
		rm_quotes_heredoc(*hereword, "$\\", -1);
	return (ret);
}
