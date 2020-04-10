/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 20:33:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_glob.h"

size_t	ft_str_wchar_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] < 0)
			i++;
		i++;
		len++;
	}
	return (len);
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
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (NULL);
	}
	ft_glob(tmp, (FT_GLOB_MARK | FT_GLOB_TILDE), NULL, &gl);
	while (gl.gl_pathv && gl.gl_pathv[i])
	{
		if (gl.gl_pathv[i][0] != '.' || to_complete[0] == '.')
			compl_tree = add_node(compl_tree, gl.gl_pathv[i], data, \
					get_color(gl.gl_pathv[i]));
		i++;
	}
	ft_globfree(&gl);
	free(tmp);
	return (compl_tree);
}
