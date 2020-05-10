/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_complete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:38:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 20:44:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "builtins.h"
#include "ft_glob.h"

int		is_exec(char *file)
{
	struct stat	st;
	int			perm;

	ft_bzero(&st, sizeof(struct stat));
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

int		test_dir(char *file)
{
	struct stat	st;

	ft_bzero(&st, sizeof(struct stat));
	lstat(file, &st);
	if (S_IFDIR & st.st_mode)
		return (1);
	return (0);
}

char	*stick_path_complete(char *path, char *to_complete)
{
	char	*tmp;
	int		len;

	len = ft_strlen(path);
	if (*path && (len == 0 || path[len - 1] != '/'))
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strjoin(path, "");
	tmp = ft_strjoin_free(ft_strjoin_free(tmp, to_complete, 1), "*", 1);
	return (tmp);
}

t_node	*get_cmd_compl(t_node *compl_tree, char *to_complete, char *path, \
		t_data *data)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(to_complete);
	i = 0;
	tmp = path;
	while (path && (tmp = ft_strchr(tmp, ':')))
	{
		tmp[0] = 0;
		compl_tree = search_in_path(stick_path_complete(path, to_complete), \
				compl_tree, data, is_exec);
		tmp++;
		path = tmp;
	}
	while (g_builtins[i].key[0])
	{
		if (ft_strnequ(to_complete, g_builtins[i].key, len))
			compl_tree = add_node(compl_tree, (char *)g_builtins[i].key, data, \
					"\033[37m");
		i++;
	}
	return (compl_tree);
}
