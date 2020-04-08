#include "ft_readline.h"
#include "builtins.h"
#include "ft_glob.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*new_str;

	if (!(new_str = ft_strjoin(s1, s2)))
		return (NULL);
	if (to_free & 1)
		free(s1);
	if (to_free & 2)
		free(s2);
	return (new_str);
}

char	*get_filename(char *path)
{
	char	*tmp;
	int		i;

	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] != '/')
		i--;
	if (i < 0)
		tmp = path;
	else
		tmp = path + i + 1;
	return (tmp);
}

int		is_exec(char *file)
{
	struct stat	st;
	int			perm;

	stat(file, &st);
	perm = (st.st_mode & S_IRWXU) / 64;
	if (perm % 2 != 0)
		return (1);
	perm = (st.st_mode & S_IRWXG) % 64 / 8;
	if (perm % 2 != 0)
		return (1);
	perm = (st.st_mode & S_IRWXO) % 8;
	if (perm % 2 != 0)
		return (1);
	return (0);
}

t_node	*search_in_path(char *to_complete, char *path, t_node *compl_tree, \
		t_data *data)
{
	char	*tmp;
	t_glob	gl;
	int		i;

	i = 0;
	ft_bzero(&gl, sizeof(gl));
	if (!(tmp = ft_strjoin_free(ft_strjoin_free(ft_strjoin(path, "/"), \
						to_complete, 1), "*", 1)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (NULL);
	}
	ft_glob(tmp, FT_GLOB_MARK, NULL, &gl);
	while (gl.gl_pathv && gl.gl_pathv[i])
	{
		if (is_exec(gl.gl_pathv[i]) && gl.gl_pathv[i][0])
			compl_tree = add_node(compl_tree, get_filename(gl.gl_pathv[i]), \
					data, 1);
		i++;
	}
	ft_globfree(&gl);
	free(tmp);
	return (compl_tree);
}

t_node	*get_cmd_compl(char *to_complete, char *path, t_data *data)
{
	t_node	*compl_tree;
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(to_complete);
	i = 0;
	compl_tree = NULL;
	tmp = path;
	while ((tmp = ft_strchr(tmp, ':')))
	{
		tmp[0] = 0;
		compl_tree = search_in_path(to_complete, path, compl_tree, data);
		tmp++;
		path = tmp;
	}
	while (g_builtins[i].key[0])
	{
		if (ft_strnequ(to_complete, g_builtins[i].key, len))
			compl_tree = add_node(compl_tree, (char *)g_builtins[i].key, data, \
					8);
		i++;
	}
	return (compl_tree);
}
