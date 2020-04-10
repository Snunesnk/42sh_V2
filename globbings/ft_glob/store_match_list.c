/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_match_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:34:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 12:34:12 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_glob_internal.h"

int			void_strcmp(void *s1, void *s2)
{
	return (ft_strcmp((char *)s1, (char *)s2));
}

static void	build_pathv(t_glob *pglob, char **new_pathv, \
			t_list *match, int append)
{
	size_t	i;

	i = pglob->gl_offs;
	if (append)
	{
		while (i < pglob->gl_pathc)
		{
			new_pathv[i] = pglob->gl_pathv[i];
			++i;
		}
		ft_memdel((void **)&pglob->gl_pathv);
	}
	while (match)
	{
		new_pathv[i++] = (char *)match->content;
		match->content = NULL;
		match = match->next;
	}
	pglob->gl_pathc = i - pglob->gl_offs;
	pglob->gl_pathv = new_pathv;
}

int			store_match_list(t_glob *pglob, t_glob_internal *gl, \
			t_list *match)
{
	char	**new_pathv;
	size_t	new_pathv_size;

	new_pathv_size = (size_t)ft_lst_size(match);
	if (gl->flags & FT_GLOB_DOOFFS)
		new_pathv_size += pglob->gl_offs;
	if (gl->flags & FT_GLOB_APPEND)
		new_pathv_size += pglob->gl_pathc;
	new_pathv = (char **)check_mem(gl,
		(void *)ft_memalloc((new_pathv_size + 1) * sizeof(char *)));
	if (!gl->ret)
	{
		pglob->gl_offs = !(gl->flags & FT_GLOB_DOOFFS) ?
			0 : pglob->gl_offs;
		build_pathv(pglob, new_pathv, match,
			gl->flags & FT_GLOB_APPEND);
	}
	ft_lstdel(&match, del_match);
	return (gl->ret);
}
