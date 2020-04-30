/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:32:41 by snunes            #+#    #+#             */
/*   Updated: 2020/04/30 12:19:18 by snunes           ###   ########.fr       */
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
	int	align;

	align = 1;
	if (!g_hist || !g_hist->history_content)
		return (NULL);
	if (g_hist->nb_line == 0)
		return (g_hist->history_content);
	if (g_hist->offset > 0 && !g_hist->history_content[g_hist->offset])
		g_hist->offset -= 1;
	while (g_hist->offset > 0 && g_hist->history_content[g_hist->offset])
		g_hist->offset -= 1;
	if (g_hist->offset == 0)
		align = 0;
	if (g_hist->nb_line > 0)
		g_hist->nb_line -= 1;
	return (g_hist->history_content + g_hist->offset + align);
}

char	*next_hist(void)
{
	if (!g_hist->history_content || !g_hist)
		return (NULL);
	if (g_hist->nb_line == g_hist->total_lines)
		return (g_hist->history_content + g_hist->offset + 1);
	if (!g_hist->history_content[g_hist->offset] \
			&& g_hist->offset + 1 < g_hist->used)
		g_hist->offset++;
	while (g_hist->history_content[g_hist->offset])
		g_hist->offset++;
	if (g_hist->nb_line < g_hist->total_lines)
		g_hist->nb_line += 1;
	return (g_hist->history_content + g_hist->offset + 1);
}

void	hist_free(void)
{
	free(g_hist->history_content);
	free(g_hist);
	g_hist = NULL;
	free(g_hist_loc);
}

void	free_hist(void)
{
	int				fd;
	unsigned int	i;
	unsigned int	last;

	if (g_shell_is_interactive && g_hist_loc && \
			(fd = open(g_hist_loc, (O_WRONLY | O_CREAT | O_TRUNC), 0644)) >= 0)
	{
		i = 0;
		last = 0;
		while (g_hist && i < g_hist->used)
		{
			if (!g_hist->history_content[i])
			{
				write(fd, g_hist->history_content + last, i - last);
				i += write(fd, "\n\0", 2) - 1;
				last = i;
			}
			i++;
		}
		close(fd);
	}
	if (g_hist)
		hist_free();
}
