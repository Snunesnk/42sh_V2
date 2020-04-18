/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:38:33 by simon             #+#    #+#             */
/*   Updated: 2020/04/18 20:36:33 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>

int		ft_putfirst(char *buff, char tofind)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (buff[i] != tofind && buff[i])
		i++;
	if (buff[i])
		i++;
	while (buff[i])
	{
		buff[pos] = buff[i];
		pos++;
		i++;
	}
	buff[pos] = '\0';
	return (1);
}

int		ft_find(char **line, char *buff)
{
	char	*tmp;
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			tmp = *line;
			if (!(*line = ft_strjoin(*line, buff)))
				return (-1);
			free(tmp);
			buff[i] = '\n';
			return (2);
		}
		i++;
	}
	return (1);
}

int		ft_fill_line(char **line, char *buff, int fd)
{
	char	*tmp;
	int		state;

	if (!*buff)
	{
		state = read(fd, buff, BUFF_SIZE);
		if (state == -1 || (!*buff && state == 0 && !**line))
			return (state);
		buff[state] = '\0';
	}
	state = ft_find(line, buff);
	if (state == -1 || state == 2)
		return (state);
	tmp = *line;
	*line = ft_strjoin(*line, buff);
	free(tmp);
	if (!*buff && *line)
		return (1);
	ft_strclr(buff);
	return ((!*line) ? -1 : ft_fill_line(line, buff, fd));
}

int		get_next_line(const int fd, char **line)
{
	int			state;
	static char	buff[FD_MAX][BUFF_SIZE + 1];

	if (!line || fd < 0 || fd > FD_MAX || BUFF_SIZE <= 0)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	state = ft_fill_line(line, buff[fd], fd);
	if (state == -1 || state == 0)
		return (state);
	if (state == 2)
		ft_putfirst((char *)buff[fd], '\n');
	return (1);
}
