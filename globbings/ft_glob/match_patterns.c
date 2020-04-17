/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:33:53 by snunes            #+#    #+#             */
/*   Updated: 2020/04/17 12:55:12 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_glob_internal.h"
#include "ft_fnmatch.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void		del_match(void *string, size_t size)
{
	(void)size;
	ft_memdel(&string);
}

t_list		*add_slash(const char *path, t_glob_internal *gl)
{
	t_list		*lst;
	const char	*file;

	file = (const char *)check_mem(gl, (void *)ft_strjoin(path, "/"));
	if (!file)
		return (NULL);
	if (!(lst = (t_list *)check_mem(gl, (void *)ft_lstnew(NULL, 0))))
	{
		ft_memdel((void **)&file);
		return (NULL);
	}
	lst->content = (void *)file;
	return (lst);
}

t_list		*find_file(const char *path, const char *cur_pattern,
			int last, t_glob_internal *gl)
{
	t_list		*match;
	t_file_data	fid;

	if (!init_file(&fid, path, cur_pattern, gl))
		return (NULL);
	match = NULL;
	if (last || fid.dir)
		match = (t_list *)check_mem(gl, (void *)ft_lstnew(NULL, 0));
	if (match)
		match->content = (void *)fid.pathname;
	else
		ft_memdel((void **)&fid.pathname);
	return (match);
}

t_list		*match_files(const char *path, const char *cur_pattern,
			int last, t_glob_internal *gl)
{
	t_list			*match;
	DIR				*dirp;
	t_file_data		fid;
	struct dirent	*fp;

	match = NULL;
	if (!(dirp = opendir(path ? path : ".")))
	{
		set_read_error(gl, path, errno);
		return (NULL);
	}
	while (!gl->ret && (fp = readdir(dirp)))
	{
		if (init_file(&fid, path, fp->d_name, gl) && (last || fid.dir)
			&& !ft_fnmatch(cur_pattern, fp->d_name, gl->fnmflags))
			ft_lstadd(&match, add_file_lst(&fid.pathname, fid.dir
				&& last && (gl->flags & FT_GLOB_MARK), gl));
		else if (fid.pathname)
			ft_memdel((void **)&fid.pathname);
	}
	if (errno)
		set_read_error(gl, path, errno);
	closedir(dirp);
	return (match);
}

t_list		*match_next_pattern(t_glob_internal *gl, const char *pattern,
			t_list *match)
{
	t_list	*ptr;
	t_list	*result;
	t_list	*next_lst;

	result = NULL;
	ptr = match;
	while (!gl->ret && ptr)
	{
		next_lst = ft_glob_internal(gl, pattern, ptr->content);
		ft_lst_merge(&result, next_lst);
		ptr = ptr->next;
	}
	ft_lstdel(&match, del_match);
	if (gl->ret)
		ft_lstdel(&result, del_match);
	return (result);
}
