/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 22:28:07 by snunes            #+#    #+#             */
/*   Updated: 2020/04/12 12:05:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "ft_readline.h"

# define ARROW_DOWN		4348699
# define ARROW_UP		4283163
# define ARROW_LEFT		4479771
# define ARROW_RIGHT	4414235

# define SPACES "                                                           "

typedef struct	s_print_list
{
	char	*content;
	size_t	used;
	size_t	capacity;
}				t_print_list;

int				g_autocompl_on;
union u_buffer	g_autocompl_bad_seq;

void			autocomplete(void);
t_node			*get_cmd_compl(char *to_complete, char *path, t_data *data);
t_node			*get_file_compl(char *to_complete, t_data *data);
t_data			*init_data(void);
t_data			*fill_data(t_data *data, t_node *compl_tree);
void			print_tree(t_node *compl_tree, t_data *data, int to_print);
void			update_exec(union u_buffer c, t_data *data);
void			display_compl(t_node *compl_tree, t_data *data);
int				calc_left_arrow(t_data *data);
int				ft_str_isspace(char *str);
void			insert_compl(t_node *compl_tree, t_data *data);
size_t			ft_str_wchar_len(char *str);
int				get_compl_start(void);
t_print_list	*get_list_compl(t_print_list *list_compl, t_data *data);
t_print_list	add_compl(t_print_list list_compl, int to_print, \
		t_data *data, t_node *compl_tree);
t_print_list	list_compl_add(t_print_list list_compl, char *to_add);
int				is_exec(char *file);
size_t			ft_str_wchar_len(char *str);

#endif
