/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:33:25 by snunes            #+#    #+#             */
/*   Updated: 2020/05/23 12:33:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_internal.h"
#include <sys/stat.h>

void		set_read_error(t_glob_internal *gl, const char *pathname, int err)
{
	if ((gl->errf && gl->errf(pathname, err))
		|| (gl->flags & FT_GLOB_ERR))
		gl->ret = FT_GLOB_ABORTED;
}

char		*add_to_path(const char *path, const char *to_add)
{
	char	*pathname;

	if (!path)
		return (ft_strdup(to_add));
	if (!(pathname = ft_strnew(ft_strlen(path) + ft_strlen(to_add) + 1)))
		return (NULL);
	pathname = ft_strcat(pathname, path);
	if (path[ft_strlen(path) - 1] != '/')
		ft_strcat(pathname, "/");
	pathname = ft_strcat(pathname, to_add);
	return (pathname);
}

int			is_dir(const char *pathname, t_glob_internal *gl)
{
	struct stat	statbuf;

	ft_bzero((void *)&statbuf, sizeof(struct stat));
	if (stat(pathname, &statbuf) == -1 && lstat(pathname, &statbuf) == -1)
	{
		set_read_error(gl, pathname, 1);
		return (-1);
	}
	return (S_ISDIR(statbuf.st_mode));
}

t_file_data	*init_file(t_file_data *dest, const char *path, \
			const char *name, t_glob_internal *gl)
{
	char	*tmp;

	dest->name = name;
	if (!(dest->pathname = (const char *)check_mem(gl,
		(void *)add_to_path(path, name))))
		return (NULL);
	if ((dest->dir = is_dir(dest->pathname, gl)) == -1)
	{
		ft_memdel((void **)&dest->pathname);
		return (NULL);
	}
	if (gl->flags & FT_GLOB_ESCAPE)
	{
		tmp = (char *)check_mem(gl, (void *)ft_escape_spec(dest->pathname,
			SHELL_SPECIAL_CHARS));
		ft_memdel((void **)&dest->pathname);
		dest->pathname = tmp;
	}
	return (dest);
}

t_list		*add_file_lst(const char **file, int add_slash, \
			t_glob_internal *gl)
{
	const char	*tmp;
	t_list		*lst;

	if (add_slash)
	{
		tmp = *file;
		*file = (const char *)check_mem(gl,
			(void *)ft_strjoin(*file, "/"));
		ft_memdel((void **)&tmp);
		if (!*file)
			return (NULL);
	}
	if (!(lst = (t_list *)check_mem(gl, (void *)ft_lstnew(NULL, 0))))
	{
		ft_memdel((void **)file);
		return (NULL);
	}
	lst->content = (void *)*file;
	return (lst);
}
