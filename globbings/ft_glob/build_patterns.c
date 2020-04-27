/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:33:14 by snunes            #+#    #+#             */
/*   Updated: 2020/04/27 12:05:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_internal.h"
#include "shell.h"

static t_list	*expand_braces(const char *pattern, t_glob_internal *gl)
{
	t_list		*pattern_list;
	const char	*start;
	const char	*end;
	const char	*exp;

	if (!(exp = get_brace_expression(gl, pattern, &start, &end)))
		return (NULL);
	if (!(start = (const char *)check_mem(gl, ft_strndup(
		pattern, start - pattern))))
	{
		ft_memdel((void **)&exp);
		return (NULL);
	}
	if (!(end = (const char *)check_mem(gl, ft_strdup(end + 1))))
	{
		ft_memdel((void **)&exp);
		ft_memdel((void **)&start);
		return (NULL);
	}
	if ((pattern_list = build_brace_patterns(start, end, exp, gl)))
		expand_pattern_list(&pattern_list, gl);
	ft_memdel((void **)&start);
	ft_memdel((void **)&end);
	ft_memdel((void **)&exp);
	return (pattern_list);
}

void			expand_pattern_list(t_list **pattern_list, t_glob_internal *gl)
{
	t_list	*cur;
	t_list	*next;
	t_list	*result;

	result = NULL;
	while (!gl->ret && (cur = ft_lst_pop(pattern_list, 0)))
	{
		if ((next = expand_braces(cur->content, gl)))
		{
			ft_lstdel(&cur, del_match);
			ft_lst_merge(&result, next);
		}
		else
			ft_lst_merge(&result, cur);
	}
	if (gl->ret)
	{
		ft_lstdel(&result, del_match);
		ft_lstdel(pattern_list, del_match);
	}
	else
		*pattern_list = result;
}

t_list			*build_patterns(const char *pattern, t_glob_internal *gl)
{
	t_list	*pattern_list;

	pattern_list = (t_list *)check_mem(gl,
		(void *)ft_lstnew((void *)pattern,
		ft_strlen(pattern) + 1));
	if (!gl->ret && (gl->flags & FT_GLOB_BRACE))
		expand_pattern_list(&pattern_list, gl);
	if (!gl->ret && (gl->flags & FT_GLOB_TILDE))
		treat_single_exp((char **)&(pattern_list->content), 1);
	return (pattern_list);
}
