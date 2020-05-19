/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:38:12 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/19 17:25:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "quotes.h"

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
		ret = replace_expansion(str, &next, ref);
	if (ret)
		psherror(ret, *str, e_cmd_type);
	return (ret);
}

static int	rm_quotes_heredoc(char *str)
{
	while (*str)
	{
		if (*str == '\\' && str[1] && ft_strchr("$\\", str[1]))
			str = (char *)ft_memmove((void *)str,
				(void *)str + 1, ft_strlen(str + 1) + 1);
		++str;	
	}
	return (0);
}

int			expand_heredoc(char **hereword)
{
	int		ret;

	ret = treat_single_exp_heredoc(hereword);
	ret = !ret ? rm_quotes_heredoc(*hereword) : ret;
	return (ret);
}

