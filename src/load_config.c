/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 10:54:58 by snunes            #+#    #+#             */
/*   Updated: 2020/04/30 11:27:09 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_config_file_loc(void)
{
	char	*home;
	char	*congig_file;

	if (!(home = getenv("HOME")))
		return (NULL);
	if (!(congig_file = ft_strjoin(home, "/.ftshrc")))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	return (congig_file);
}

void		load_config(void)
{
	char	*congig_file;
	char	*line;
	int		fd;

	if (!(congig_file = get_config_file_loc()))
		return ;
	if ((fd = open(congig_file, (O_RDONLY | O_CREAT), 644)) < 0)
		return ;
	free(congig_file);
	while (get_stdin(fd, &line) > 0)
	{
		if (*line != '#')
			exec_input(line);
		free(line);
	}
}
