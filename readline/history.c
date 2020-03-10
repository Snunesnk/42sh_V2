#include "ft_readline.h"

struct s_hist	*g_hist = NULL;
char		*g_vline = NULL;
char		*g_hist_loc = NULL;

void		init_history(void)
{
	char	buf[10000];
	int		fd;

	ft_bzero(buf, 10000);
	get_history_loc();
	if (!(g_hist = (struct s_hist *)ft_memalloc(sizeof(*g_hist))))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	g_hist->history_content = NULL;
	g_hist->offset = 0;
	g_hist->used = 0;
	g_hist->capacity = 0;
	g_hist->total_lines = 1;
	if ((fd = open(g_hist_loc, (O_RDWR | O_CREAT), 0644)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "./21sh: error: can't open %s\n", g_hist_loc);
		return ;
	}
	while (read(fd, buf, 10000) > 0)
		add_hentry(buf, 0);
	remove_nl();
	g_hist->nb_line = g_hist->total_lines;
	close(fd);
}

void		remove_nl(void)
{
	unsigned int	i;

	i = 0;
	if (!g_hist || !g_hist->history_content)
		return ;
	while (i < g_hist->used)
	{
		if (g_hist->history_content[i] == '\n')
		{
			g_hist->total_lines += 1;
			g_hist->history_content[i] = '\0';
		}
		i++;
	}
	g_hist->total_lines -= 1; /*remove 1 because of increased in add_hentry */
}

void		get_history_loc(void)
{
	char	*user_home;

	user_home = NULL;
	if (g_hist_loc)
	{
		free(g_hist_loc);
		return ;
	}
	if (!(user_home = getenv("HOME")))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return ;
	}
	if (!(g_hist_loc = ft_strjoin(user_home, "/.21sh_history")))
	{
		ft_printf("./12sh: cannot allocate memory\n");
		return ;
	}
}

void		add_hentry(const char *buf, int mode)
{
	int	size;

	size = ft_strlen(buf);
	if (size + g_hist->used >= g_hist->capacity - 5 || !g_hist->capacity)
	{
		if (!g_hist->capacity)
			g_hist->capacity = 1;
		if (!(g_hist->history_content = (char *)ft_memrealloc( \
						(void **)&(g_hist->history_content), g_hist->used, \
						sizeof(char) * (g_hist->capacity + size) * 3)))
		{
			ft_dprintf(STDERR_FILENO, "/.21sh: cannot allocate memory\n");
			return ;
		}
		g_hist->capacity = (g_hist->capacity + size) * 3;
	}
	ft_strcpy(g_hist->history_content + g_hist->used, buf);
	g_hist->used += size + mode;
	g_hist->offset = g_hist->used - 1;
	g_hist->total_lines += 1;
	g_hist->nb_line = g_hist->total_lines;
}

char	*prev_hist(void)
{
	int	align;

	align = 1;
	if (!g_hist || !g_hist->history_content)
		return (NULL);
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
	if (!g_hist->history_content[g_hist->offset] \
			&& g_hist->offset + 1 < g_hist->used)
		g_hist->offset++;
	while (g_hist->history_content[g_hist->offset])
		g_hist->offset++;
	if (g_hist->history_content[g_hist->offset + 1])
		g_hist->nb_line += 1;
	return (g_hist->history_content + g_hist->offset + 1);

}

void	free_hist(void)
{
	int	fd;
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
