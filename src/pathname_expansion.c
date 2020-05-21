/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:13:01 by snunes            #+#    #+#             */
/*   Updated: 2020/05/21 22:01:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "libft.h"
#include "error.h"
#include "shell.h"
#include "quotes.h"

int			replace_fields(t_process *p, int i, char **av, int ac)
{
	int		new_argc;
	char	**new_argv;

	ft_memdel((void **)p->argv + i);
	if (ac > 1)
	{
		new_argc = p->argc + ac - 1;
		if (!(new_argv = ft_memalloc((new_argc + 1) * sizeof(char *))))
			return (e_cannot_allocate_memory);
		ft_memcpy(new_argv, p->argv, i * sizeof(char *));
		ft_memcpy(new_argv + i + ac, p->argv + i + 1,
			(p->argc - i - 1) * sizeof(char *));
		ft_memdel((void **)&p->argv);
		p->argv = new_argv;
		p->argc = new_argc;
	}
	ft_memcpy(p->argv + i, av, ac * sizeof(char *));
	ft_bzero(av, ac * sizeof(char *));
	return (e_success);
}

static char	*build_glob_pattern(const char *arg)
{
	int		qmode;
	int		old_qmode;
	char	*ptr;
	char	*pattern;

	if (!(pattern = ft_strnew(ft_strlen(arg) * 2)))
		return (NULL);
	ft_strcpy(pattern, arg);
	ptr = pattern;
	qmode = NO_QUOTE;
	while (*ptr)
	{
		old_qmode = qmode;
		qmode = get_qmode(old_qmode, *ptr);
		if (qmode != (old_qmode & ~BSQUOTE) && qmode != BSQUOTE)
			ft_memmove((void *)ptr, (void *)ptr + 1, ft_strlen(ptr + 1) + 1);
		else if ((qmode & ~BSQUOTE) && !(qmode & BSQUOTE)
			&& !(old_qmode & BSQUOTE) && ft_strchr("\\{}?[]*", *ptr))
		{
			ft_memmove((void *)ptr + 1, (void *)ptr, ft_strlen(ptr) + 1);
			*ptr = '\\';
			ptr += 2;
		}
		else
			++ptr;
	}
	return (pattern);
}

/*
** TODO: find a way not to copy the string each time and to use GLOB_APPEND
** instead of copying the entire argv each time
*/

int			pathname_expansion(t_process *p, int i, int *skip)
{
	t_glob	gl;
	int		ret;
	char	*pattern;

	if (!has_unquoted_spec_chars(p->argv[i], "{?[*"))
		return (e_success);
	ft_bzero(&gl, sizeof(t_glob));
	if (!(pattern = build_glob_pattern(p->argv[i])))
		return (e_cannot_allocate_memory);
	ret = ft_glob(pattern, FT_GLOB_BRACE, NULL, &gl);
	ft_memdel((void **)&pattern);
	if (!ret)
	{
		*skip = gl.gl_pathc;
		ret = replace_fields(p, i, gl.gl_pathv, *skip);
		ft_globfree(&gl);
		return (ret);
	}
	else if (ret == FT_GLOB_NOSPACE)
		return (e_cannot_allocate_memory);
	else if (ret == FT_GLOB_ABORTED)
		return (e_system_call_error);
	return (e_success);
}
