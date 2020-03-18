#include "ft_glob_internal.h"
#include <sys/stat.h>
#include <errno.h>

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
	ft_strcpy(pathname, path);
	if (path[ft_strlen(path) - 1] != '/')
		ft_strcat(pathname, "/");
	ft_strcat(pathname, to_add);
	return (pathname);
}

int		is_dir(const char *pathname, t_glob_internal *gl)
{
	struct stat	statbuf;
	
	ft_bzero((void *)&statbuf, sizeof(struct stat));
	if (stat(pathname, &statbuf) == -1)
	{
		set_read_error(gl, pathname, errno);
		return (-1);
	}
//	return ((statbuf.st_mode & S_IFMT) == S_IFDIR);
	return (S_ISDIR(statbuf.st_mode)); //is this leeegul ?
}

t_file_data	*init_file(t_file_data *dest, const char *path,
			const char *name, t_glob_internal *gl)
{
	dest->name = name;
	if (!(dest->pathname = (const char *)check_mem(gl,
		(void *)add_to_path(path, name))))
		return (NULL);
	else if ((dest->dir = is_dir(dest->pathname, gl)) == -1)
	{
		ft_memdel((void **)&dest->pathname);
		return (NULL);
	}
	return (dest);
}

t_list		*add_file_lst(const char **file, int add_slash,
			t_glob_internal *gl)
{
	const char 	*tmp;
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

