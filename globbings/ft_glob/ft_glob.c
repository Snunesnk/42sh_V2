/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:33:33 by snunes            #+#    #+#             */
/*   Updated: 2020/04/27 12:05:50 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_internal.h"
#include "ft_fnmatch.h"

static int		set_fnmflags(int flags)
{
	int	fnmflags;

	fnmflags = FT_FNM_PATHNAME;
	if (flags & FT_GLOB_NOESCAPE)
		fnmflags |= FT_FNM_NOESCAPE;
	if (!(flags & FT_GLOB_PERIOD))
		fnmflags |= FT_FNM_PERIOD;
	return (fnmflags);
}

static t_list	*exec_patterns(t_list **pattern_list, t_glob_internal *gl)
{
	const char	*path;
	t_list		*ptr;
	t_list		*next;
	t_list		*match;

	match = NULL;
	ptr = *pattern_list;
	while (!gl->ret && ptr)
	{
		path = ((char *)ptr->content)[0] == '/' ? "/" : NULL;
		next = ft_glob_internal(gl, ptr->content, path);
		if (!gl->ret && next && !(gl->flags & FT_GLOB_NOSORT))
			ft_lst_quicksort(next, ft_lst_size(next), void_strcmp);
		ft_lst_merge(&match, next);
		ptr = ptr->next;
	}
	if (gl->ret)
		ft_lstdel(&match, del_match);
	ft_lstdel(pattern_list, del_match);
	return (match);
}

void			ft_globfree(t_glob *pglob)
{
	size_t	i;

	i = pglob->gl_offs;
	while (i < pglob->gl_offs + pglob->gl_pathc)
		ft_memdel((void **)pglob->gl_pathv + i++);
	ft_memdel((void **)&pglob->gl_pathv);
	ft_bzero((void *)pglob, sizeof(t_glob));
}

/*
** TODO: Think about a clean way to handle memory allocations
*/

int				ft_glob(const char *pattern, int flags,\
		int (*errfunc)(const char *epath, int eerrno), t_glob *pglob)
{
	t_glob_internal	gl;
	t_list			*match;
	t_list			*pattern_list;

	gl.errf = errfunc;
	gl.flags = flags;
	gl.fnmflags = set_fnmflags(flags);
	gl.ret = 0;
	match = NULL;
	pattern_list = build_patterns(pattern, &gl);
	if (!gl.ret)
		match = exec_patterns(&pattern_list, &gl);
	if (!gl.ret && !match)
	{
		if (flags & FT_GLOB_NOCHECK)
			match = (t_list *)check_mem(&gl,
				(void *)ft_lstnew((void *)pattern,
				ft_strlen(pattern + 1)));
		else
			return (FT_GLOB_NOMATCH);
	}
	return (gl.ret ? gl.ret : store_match_list(pglob, &gl, match));
}
