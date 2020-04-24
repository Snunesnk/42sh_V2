/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:57:39 by snunes            #+#    #+#             */
/*   Updated: 2020/04/24 17:46:39 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_internal.h"

int		is_shell_spec(char c)
{
	return (!!ft_strchr(SHELL_SPECIAL_CHARS, c));
}

int		count_shell_spec(const char *str)
{
	int	i;
	int	nb_spec;

	i = 0;
	nb_spec = 0;
	while (str[i])
	{
		if (is_shell_spec(str[i]))
			nb_spec++;
		i++;
	}
	return (nb_spec);
}

char	*add_esc_to_path(char *path)
{
	char	*pathname;
	int		len;
	int		i;

	i = 0;
	if (!count_shell_spec(path))
		return (path);
	len = ft_strlen(path) + count_shell_spec(path);
	if (!(pathname = ft_strnew(len + 1)))
		return (NULL);
	while (path[i])
	{
		if (ft_strchr(SHELL_SPECIAL_CHARS, path[i]))
			ft_strcat(pathname, "\\");
		ft_strncat(pathname, path + i, 1);
		i++;
	}
	free(path);
	return (pathname);
}
