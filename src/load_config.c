/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 10:54:58 by snunes            #+#    #+#             */
/*   Updated: 2020/05/09 14:11:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_config_file_loc(void)
{
	char	*home;
	char	*congig_file;

	if (!(home = getenv("HOME")))
		return (NULL);
	if (!(congig_file = ft_strjoin(home, "/.monkeyshellrc")))
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
	fd = open(congig_file, (O_RDONLY | O_CREAT), 644);
	free(congig_file);
	if (fd < 0)
		return ;
	while ((line = get_input_fd(fd, 1, NULL)))
	{
		if (*line != '#')
			exec_input(line);
		else
			free(line);
	}
	free(line);
}
