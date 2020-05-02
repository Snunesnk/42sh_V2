/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:35:33 by snunes            #+#    #+#             */
/*   Updated: 2020/05/02 23:13:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "error.h"
#include "shell.h"

struct s_hist	*g_hist = NULL;
char		*g_vline = NULL;
char		*g_hist_loc = NULL;

void	init_history(void)
{
	char		*buf;
	int			fd;
	struct stat	st;

	buf = NULL;
	if (!(g_hist = (struct s_hist *)ft_memalloc(sizeof(*g_hist))))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	g_hist->history_content = NULL;
	g_hist->offset = 0;
	g_hist->used = 0;
	g_hist->capacity = 0;
	g_hist->total_lines = 0;
	get_history_loc();
	if (!g_hist_loc)
		return ;
	stat(g_hist_loc, &st);
	if ((fd = open(g_hist_loc, (O_RDWR | O_CREAT), 0644)) < 0)
		return ;
	while (st.st_size > 0 && get_next_cmd(fd, &buf) > 0)
		add_hentry(buf, ft_strlen(buf), 1);
	g_hist->nb_line = g_hist->total_lines;
	close(fd);
}

void	get_history_loc(void)
{
	char	*user_home;

	user_home = NULL;
	if (g_hist_loc)
	{
		free(g_hist_loc);
		return ;
	}
	g_hist_loc = NULL;
	if (!(user_home = getenv("HOME")))
	{
		ft_printf("%s: HOME not set\n", g_progname);
		return ;
	}
	if (!(g_hist_loc = ft_strjoin(user_home, "/.monkeyshell_history")))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
}

int		is_valid_hentry(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	while (g_hist->nb_line < g_hist->total_lines)
		next_hist();
	tmp = prev_hist();
	next_hist();
	if (!tmp)
		return (1);
	if (ft_strequ(tmp, str))
		return (0);
	return (1);

}

void	add_hentry(char *buf, int size, int mode)
{
	if (!*buf || ft_str_isspace((char *)buf) || !g_shell_is_interactive)
		return ;
	if (!is_valid_hentry(buf))
		return ;
	if (size + g_hist->used >= g_hist->capacity - 5 || !g_hist->capacity)
	{
		if (!g_hist->capacity)
			g_hist->capacity = 1;
		if (!(g_hist->history_content = (char *)ft_memrealloc(\
						(void **)&(g_hist->history_content), g_hist->used, \
						sizeof(char) * (g_hist->capacity + size) * 3)))
		{
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
			return ;
		}
		g_hist->capacity = (g_hist->capacity + size) * 3;
	}
	ft_strncpy(g_hist->history_content + g_hist->used, buf, size);
	g_hist->used += size + mode;
	g_hist->offset = g_hist->used - 1;
	g_hist->total_lines += 1;
	g_hist->nb_line = g_hist->total_lines;
}

void	*ft_memrealloc(void **content, size_t old_size, size_t new_size)
{
	void	*new_content;
	char	*old_ptr;
	char	*new_ptr;
	size_t	i;

	i = 0;
	if (!(new_content = ft_memalloc(new_size)))
		return (NULL);
	old_ptr = (char *)*content;
	new_ptr = (char *)new_content;
	while (i < old_size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}
	free(*content);
	return (new_content);
}
