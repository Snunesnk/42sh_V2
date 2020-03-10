#ifndef HISTORY_H
# define HISTORY_H

# define ADD_SEPARATOR 1

struct s_hist
{
	char				*history_content;
	unsigned int		offset;
	unsigned int		used;
	unsigned int		capacity;
	int					nb_line;
	int					total_lines;
};

extern struct s_hist	*g_hist;
extern char				*g_vline;
extern char				*g_hist_loc;
extern char				*g_original_cmd;
extern int				g_hist_lookup;

void	init_history(void);
void	get_history_loc(void);
void	add_hentry(const char *buf, int mode);
char	*prev_hist(void);
char	*next_hist(void);
void	free_hist(void);
void	remove_nl(void);
void	hist_lookup(union u_buffer c);
void	*ft_memrealloc(void **content, size_t old_size, size_t new_size);
char	*hist_expanse(char *value);
char	*get_hist_entry(char *tmp);
char	*expand_num(char *value, int start, int sign);
char	*expand_word(char *value, int start, int sign);
char	*replace_hist_exp(char *value, char *hist_entry);
char	*get_matching_hist(char **line, char *patern);
char	*get_beg_matching_hist(char **line, char *patern);

#endif
