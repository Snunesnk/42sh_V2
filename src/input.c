/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:48:52 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/25 19:17:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		*create_new_line(char *str, int *len)
{
	char	*new_line;

	new_line = (char*)ft_memalloc(*len + 1);
	if (!new_line)
	{
		*len = -1;
		return (NULL);
	}
	else
	{
		if (str)
		{
			new_line = ft_strncpy(new_line, str, *len + 1);
			free(str);
		}
		return (new_line);
	}
}

static int		get_block(char **line, int len, char separator)
{
	int		ret;
	char	c;

	ret = 0;
	while (ret < len)
	{
		c = ft_getch();
		if (c == -1)
			return (-2);
		if (c == separator || !c)
		{
			(*line)[ret] = 0;
			return (ret);
		}
		(*line)[ret] = c;
		++ret;
	}
	if (ret == len)
		return (-1);
	else
		return (1);
}

int				get_stdin(char **line)
{
	int		len;
	int		ret;
	char	*new_line;

	len = 0;
	ret = 0;
	new_line = NULL;
	while (1)
	{
		len += 128;
		new_line = create_new_line(new_line, &len);
		if (len == -1 || !new_line)
			return (-1);
		*line = new_line;
		if ((ret = get_block(line, len, '\n')) == -1)
			continue ;
		if (ret == -2)
		{
			ft_memdel((void**)line);
			return (-1);
		}
		else
			return (1);
	}
	return (ret);
}
