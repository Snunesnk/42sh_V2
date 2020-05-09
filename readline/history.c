/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:35:33 by snunes            #+#    #+#             */
/*   Updated: 2020/05/09 17:49:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "error.h"
#include "shell.h"
#include "quotes.h"

struct s_hist	g_hist =
{
	.history_content = NULL,
	.hist_loc = NULL,
	.offset = 1,
	.used = 1,
	.capacity = 1,
	.nb_line = 1,
	.total_lines = 0,
	.hist_ignore = 0,
};

void	init_history(void)
{
	char		*buf;
	int			fd;
	struct stat	st;

	buf = NULL;
	if (!get_history_loc())
		return ;
	stat(g_hist.hist_loc, &st);
	if ((fd = open(g_hist.hist_loc, (O_RDWR | O_CREAT), 0644)) < 0)
		return ;
	while (st.st_size > 0 && (buf = get_input_fd(fd, FULL_QUOTE, NULL)))
	{
		add_hentry(buf, ft_strlen(buf));
		free(buf);
	}
	close(fd);
}

int		get_history_loc(void)
{
	char	*user_home;

	user_home = NULL;
	if (g_hist.hist_loc)
		free(g_hist.hist_loc);
	g_hist.hist_loc = NULL;
	if (!(user_home = get_shell_var("HOME", g_env)))
	{
		ft_printf("%s: HOME not set\n", g_progname);
		return (0);
	}
	if (!(g_hist.hist_loc = ft_strjoin(user_home, "/.monkeyshell_history")))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (0);
	}
	return (1);
}

int		is_invalid_hentry(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_hist.nb_line <= g_hist.total_lines)
		next_hist();
	if (ft_str_isspace(str) || !*str)
		return (1);
	while (str[i])
	{
		if (!ft_isprint(str[i]) && str[i] != '\n')
			return (1);
		i++;
	}
	tmp = prev_hist();
	next_hist();
	if (!tmp || g_hist.total_lines == 0)
		return (0);
	if (ft_strequ(tmp, str))
		return (1);
	return (0);
}

void	add_hentry(char *buf, int size)
{
	if (!*buf || !g_shell_is_interactive)
		return ;
	if ((g_hist.hist_ignore = is_invalid_hentry(buf)))
		return ;
	if (!g_hist.history_content || size + g_hist.used >= g_hist.capacity - 5)
	{
		if (!(g_hist.history_content = (char *)ft_memrealloc(\
						(void **)&(g_hist.history_content), g_hist.used, \
						sizeof(char) * (g_hist.capacity + size + 1) * 3)))
		{
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
			return ;
		}
		g_hist.capacity = (g_hist.capacity + size + 1) * 3;
	}
	ft_strncpy(g_hist.history_content + g_hist.used, buf, size);
	g_hist.used += size + 1;
	g_hist.offset = g_hist.used;
	g_hist.total_lines += 1;
	g_hist.nb_line = g_hist.total_lines + 1;
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
	while (old_ptr && i < old_size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}
	free(*content);
	return (new_content);
}
