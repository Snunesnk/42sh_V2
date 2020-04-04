#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "ft_readline.h"

# define ARROW_DOWN		4348699
# define ARROW_UP		4283163
# define ARROW_LEFT		4479771
# define ARROW_RIGHT	4414235

int				g_autocompl_on;
int				g_autocompl_query;
union u_buffer	g_autocompl_bad_seq;

void	autocomplete(void);
t_node	*get_cmd_compl(char *to_complete, char *path, t_data *data);
t_data	*init_data(void);;
t_data	*fill_data(t_data *data, t_node *compl_tree);
void	print_tree(t_node *compl_tree, t_data *data, int to_print);
void	print_compl(t_node *compl_tree, t_data *data);
void	update_exec(union u_buffer c, t_data *data);
void	display_compl(t_node *compl_tree, t_data *data);

#endif
