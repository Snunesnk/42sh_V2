/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_complete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:51:38 by snunes            #+#    #+#             */
/*   Updated: 2020/05/10 21:16:37 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "builtins.h"
#include "ft_glob.h"

char		*get_filename(char *path)
{
	char	*tmp;
	int		i;

	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] == '/')
		i--;
	while (i > 0 && path[i] != '/')
		i--;
	if (i <= 0)
		tmp = path;
	else
		tmp = path + i + 1;
	return (tmp);
}

t_node		*search_in_path(char *to_complete, t_node *compl_tree,\
		t_data *data, int (*test)(char *))
{
	t_glob	gl;
	int		i;

	i = 0;
	ft_bzero(&gl, sizeof(gl));
	if (!to_complete)
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	ft_glob(to_complete, (FT_GLOB_MARK | FT_GLOB_TILDE), NULL, &gl);
	while (gl.gl_pathv && gl.gl_pathv[i])
	{
		if (test(gl.gl_pathv[i]) && gl.gl_pathv[i][0])
			compl_tree = add_node(compl_tree, get_filename(gl.gl_pathv[i]), \
					data, ((test_cd()) ? "\033[1;34m" : "\033[37m"));
		i++;
	}
	ft_globfree(&gl);
	free(to_complete);
	return (compl_tree);
}

t_node		*get_cd_compl(char *path, t_data *data)
{
	t_node	*compl_tree;
	char	*tmp;

	compl_tree = NULL;
	tmp = path;
	while (tmp && *tmp)
	{
		if ((tmp = ft_strchr(path, ':')))
		{
			tmp[0] = 0;
			tmp++;
		}
		compl_tree = search_in_path(ft_strjoin(path, "*"), compl_tree, data, \
				test_dir);
		path = tmp;
	}
	return (compl_tree);
}

static char	*add_path(char *to_complete, char *real_path)
{
	char	*path;
	int		len;

	len = ft_strlen(to_complete) + ft_strlen(real_path) + 2;
	if (!(path = (char *)ft_memalloc(sizeof(char) * len)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	path = ft_strcat(path, to_complete);
	path = ft_strcat(path, ":");
	path = ft_strcat(path, real_path);
	return (path);
}

void		cd_complete(char *to_complete)
{
	char	*path;
	t_node	*compl_tree;
	t_data	*data;

	data = init_data();
	if (!*to_complete && get_shell_var("CDPATH", g_env))
		path = add_path(to_complete, get_shell_var("CDPATH", g_env));
	else
		path = ft_strdup(to_complete);
	if (!path || !data)
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	compl_tree = get_cd_compl(path, data);
	if (compl_tree)
		display_compl(compl_tree, data);
	free(data);
	free(path);
	free_node(compl_tree);
}
