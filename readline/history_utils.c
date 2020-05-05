/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:32:41 by snunes            #+#    #+#             */
/*   Updated: 2020/05/05 20:13:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "libft.h"

int		get_next_cmd(int fd, char **buf)
{
	static char	cmd[READ_SIZE];
	char		*tmp;
	static int	ret = 0;

	if (ret <= 0)
	{
		ret = read(fd, cmd, READ_SIZE - 2);
		if (!ret)
			return (0);
	}
	else
	{
		while (cmd[0])
		{
			ft_memmove(cmd, cmd + 1, ret + 1);
			ret--;
		}
		ft_memmove(cmd, cmd + 1, ret + 1);
		ret--;
	}
	tmp = ft_strstr(cmd, "\n\0");
	if (tmp)
		*tmp = '\0';
	*buf = cmd;
	return (1);
}

char	*prev_hist(void)
{
	if (!g_hist.history_content)
		return (g_line.line);
	while (g_hist.offset > 0 && !g_hist.history_content[g_hist.offset])
		g_hist.offset -= 1;
	while (g_hist.offset > 0 && g_hist.history_content[g_hist.offset])
		g_hist.offset -= 1;
	if (g_hist.nb_line > 1)
		g_hist.nb_line -= 1;
	return (g_hist.history_content + g_hist.offset + 1);
}

char	*next_hist(void)
{
	if (!g_hist.history_content)
		return (g_line.line);
	if (g_hist.offset < g_hist.used)
		g_hist.offset++;
	while (g_hist.history_content[g_hist.offset])
		g_hist.offset++;
	if (g_hist.nb_line <= g_hist.total_lines)
		g_hist.nb_line += 1;
	return (g_hist.history_content + g_hist.offset + 1);
}

void	hist_free(void)
{
	free(g_hist.history_content);
	g_hist.history_content = NULL;
	free(g_hist.hist_loc);
	g_hist.hist_loc = NULL;
}

void	free_hist(void)
{
	int				fd;
	unsigned int	i;

	if (g_shell_is_interactive && g_hist.hist_loc && \
		(fd = open(g_hist.hist_loc, (O_WRONLY | O_CREAT | O_TRUNC), 0644)) >= 0)
	{
		i = 1;
		while (i < g_hist.used)
		{
			if (!g_hist.history_content[i])
				g_hist.history_content[i] = '\n';
			i++;
		}
		write(fd, g_hist.history_content + 1, g_hist.used - 1);
		close(fd);
	}
	hist_free();
}
