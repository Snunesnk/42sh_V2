/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_complete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:51:38 by snunes            #+#    #+#             */
/*   Updated: 2020/05/09 20:13:36 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_node	*search_in_path(char *to_complete, t_node *compl_tree, t_data *data, \
		int (*test)(char *))
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

t_node	*get_cd_compl(char *to_complete, char *path, t_data *data)
{
	t_node	*compl_tree;
	char	*tmp;

	compl_tree = NULL;
	tmp = path;
	while (tmp)
	{
		if ((tmp = ft_strchr(path, ':')))
		{
			tmp[0] = 0;
			tmp++;
		}
		compl_tree = search_in_path(stick_path_complete(path, to_complete), \
				compl_tree, data, test_dir);
		path = tmp;
	}
	return (compl_tree);
}

static char	*extract_path(char *to_complete)
{
	char	*path;
	int		i;
	int		last;

	last = 0;
	i = 0;
	if (to_complete[0] != '/' && to_complete[0] != '~')
		return (ft_strdup(".:"));
	while (to_complete[i])
	{
		if (to_complete[i] == '/')
			last = i + 1;
		i++;
	}
	if (!(path = (char *)ft_memalloc(sizeof(char) * last + 2)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	path = ft_strncat(path, to_complete, last);
	path = ft_strncat(path, ":", 1);
	return (path);
}

void	cd_complete(char *to_complete)
{
	char	*path;
	t_node	*compl_tree;
	t_data	*data;

	data = init_data();
	if (get_shell_var("CDPATH", g_env))
		path = ft_strjoin_free(extract_path(to_complete), \
				get_shell_var("CDPATH", g_env), 1);
	else
		path = extract_path(to_complete);
	if (!path || !data)
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	compl_tree = get_cd_compl(to_complete, path, data);
	if (compl_tree)
		display_compl(compl_tree, data);
	free(data);
	free(path);
	free_node(compl_tree);
}
