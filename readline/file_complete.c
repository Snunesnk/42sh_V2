/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/06/04 12:24:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_glob.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "error.h"

size_t	ft_str_wchar_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] < 0 && str[i + 1])
			i++;
		i++;
		len++;
	}
	return (len);
}

int		test_cmd(char *to_find, int len)
{
	static char	operator[] = "&|;<>";
	int			i;

	if (g_line.len < len)
		return (0);
	i = g_line.c_pos - 1;
	while (i > 0 && !ft_strchr(operator, g_line.line[i]))
		i--;
	if (ft_strchr(operator, g_line.line[i]))
		i++;
	while (g_line.line[i] && ft_isspace(g_line.line[i]))
		i++;
	if (g_line.line[i] && ft_strnequ(g_line.line + i, to_find, len))
		return (1);
	return (0);
}

t_node	*get_file_compl(char *to_complete, t_data *data)
{
	t_node	*compl_tree;
	char	*tmp;
	t_glob	gl;
	int		i;

	i = 0;
	compl_tree = NULL;
	ft_bzero(&gl, sizeof(gl));
	if (!(tmp = ft_strjoin(to_complete, "*")))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	ft_glob(tmp, (FT_GLOB_MARK | FT_GLOB_TILDE | FT_GLOB_ESCAPE), NULL, &gl);
	while (gl.gl_pathv && gl.gl_pathv[i])
	{
		if ((gl.gl_pathv[i][0] != '.' || to_complete[0] == '.'))
			compl_tree = add_node(compl_tree, gl.gl_pathv[i], data, \
					get_color(gl.gl_pathv[i]));
		i++;
	}
	ft_globfree(&gl);
	free(tmp);
	return (compl_tree);
}
