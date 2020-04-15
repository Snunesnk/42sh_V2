/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:13:01 by snunes            #+#    #+#             */
/*   Updated: 2020/04/15 12:29:04 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "libft.h"
#include "error.h"
#include "shell.h"

static int	replace_pattern(t_process *p, int i, t_glob *gl, int *skip)
{
	int		new_argc;
	char	**new_argv;

	ft_memdel((void **)p->argv + i);
	if (gl->gl_pathc > 1)
	{
		new_argc = p->argc + gl->gl_pathc - 1;
		if (!(new_argv = ft_memalloc((new_argc + 1) * sizeof(char *))))
			return (e_cannot_allocate_memory);
		ft_memcpy(new_argv, p->argv, i * sizeof(char *));
		ft_memcpy(new_argv + i + gl->gl_pathc, p->argv + i + 1,
			(p->argc - i - 1) * sizeof(char *));
		ft_memdel((void **)&p->argv);
		p->argv = new_argv;
		p->argc = new_argc;
	}
	ft_memcpy(p->argv + i, gl->gl_pathv, gl->gl_pathc * sizeof(char *));
	ft_bzero(gl->gl_pathv, gl->gl_pathc * sizeof(char *));
	*skip = gl->gl_pathc;
	ft_globfree(gl);
	return (e_success);
}

/*
** TODO: find a way not to copy the string each time and to use GLOB_APPEND
** instead of copying the entire argv each time
*/

int			pathname_expansion(t_process *p, int i, int *skip)
{
	t_glob	gl;
	int		ret;

	ft_bzero(&gl, sizeof(t_glob));
	ret = ft_glob(p->argv[i], FT_GLOB_BRACE, NULL, &gl);
	if (!ret)
		return (replace_pattern(p, i, &gl, skip));
	else if (ret == FT_GLOB_NOSPACE)
		return (e_cannot_allocate_memory);
	else if (ret == FT_GLOB_ABORTED)
		return (e_system_call_error);
	return (e_success);
}
