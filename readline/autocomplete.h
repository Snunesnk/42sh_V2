#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "ft_readline.h"

void	autocomplete(void);
t_node	*get_cmd_compl(char *to_complete, char *path, t_data *data);
t_data	*init_data(void);;
void	print_tree(t_node *compl_tree);

#endif
