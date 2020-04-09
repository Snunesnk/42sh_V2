/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:40:31 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

# include "ft_readline.h"

typedef struct	s_node
{
	struct s_node	*right;
	struct s_node	*left;
	char			*name;
	int				length;
	int				heigth;
	int				color;
	int				nb_node;
}				t_node;

typedef struct	s_data
{
	int	name_l;
	int	column;
	int	row;
	int	nb_line;
	int	name_p_line;
	int	chosen_exec;
	int	nb_exec;
	int	type;
	int	first_print;
	int	last_print;
}				t_data;

t_node	*add_node(t_node *tree, char *name, t_data *data, int color);
void	free_node(t_node *node);
int		check_balance(t_node *node);
t_node	*balance(int balanced, t_node *node, t_node *new_node);
int		max(int a, int b);
int		heigth(t_node *node);
int		ft_node_cmp(t_node *tree, t_node *node);

#endif
