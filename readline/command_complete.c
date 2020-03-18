#include "ft_readline.h"
#include "builtins.h"

int		is_exec(struct dirent *file, char *root)
{
	char		*path;
	char		*tmp;
	struct stat	st;
	int			perm;

	path = ft_strjoin(root, "/");
	tmp = ft_strjoin(path, file->d_name);
	if (!path || !tmp)
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (0);
	}
	free(path);
	stat(tmp, &st);
	free(tmp);
	perm = (st.st_mode & S_IRWXU) / 64;
	if (perm % 2 != 0 && file->d_type != 4)
		return (1);
	perm = (st.st_mode & S_IRWXG) % 64 / 8;
	if (perm % 2 != 0 && file->d_type != 4)
		return (1);
	perm = (st.st_mode & S_IRWXO) % 8;
	if (perm % 2 != 0 && file->d_type != 4)
		return (1);
	return (0);
}

t_node	*search_in_path(char *to_complete, char *path, t_node *compl_tree, \
		t_data *data)
{
	DIR				*dir;
	struct dirent	*file;
	int				len;

	(void)file;
	(void)data;
	(void)len;
	len = ft_strlen(to_complete);
	if (!(dir = opendir(path)))
		return (compl_tree);
/*	while ((file = readdir(dir)))
	{
		if ((ft_strnseem(to_complete, file->d_name, len)) \
				&& is_exec(file))
			compl_tree = add_node(compl_tree, file->d_name, 1);
	}*/
	closedir(dir);
	return (compl_tree);
}

t_node	*get_cmd_compl(char *to_complete, char *path, t_data *data)
{
	t_node	*compl_tree;
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(to_complete);
	i = 0;
	tmp = path;
	compl_tree = NULL;
	while ((tmp = ft_strchr(tmp, ':')))
	{
		tmp[0] = 0;
		compl_tree = search_in_path(to_complete, path, compl_tree, data);
		path = tmp;
		tmp++;
	}
	while (g_builtins[i].key[0])
	{
		if (ft_strnequ(to_complete, g_builtins[i].key, len))
			compl_tree = add_node(compl_tree, (char *)g_builtins[i].key, data, 8);
		i++;
	}
	return (compl_tree);
}
