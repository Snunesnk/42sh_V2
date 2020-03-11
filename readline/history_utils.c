/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:32:41 by snunes            #+#    #+#             */
/*   Updated: 2020/03/11 19:12:34 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

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

void	free_hist(void)
{
	int				fd;
	unsigned int	i;

	if ((fd = open(g_hist_loc, (O_WRONLY | O_CREAT | O_TRUNC), 0644)) < 0)
		ft_printf("./21sh: cannot open %s\n", g_hist_loc);
	else
	{
		i = 0;
		while (i <= g_hist->used)
		{
			if (!g_hist->history_content[i])
				g_hist->history_content[i] = '\n';
			i++;
		}
		write(fd, g_hist->history_content, g_hist->used);
		close(fd);
	}
	free(g_hist->history_content);
	free(g_hist);
	free(g_hist_loc);
}
