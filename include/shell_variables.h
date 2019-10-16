/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:22:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/14 14:44:13 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_VARIABLES_H
# define SHELL_VARIABLES_H

struct	s_shvar
{
	char				*value;
	struct s_shvar		*next_var;
	struct s_shvar		*next_content;
	unsigned long long	index:63;
	_Bool				isarray:1;	
};

extern struct s_shvar		*g_shellvar;

int	initialize_shell_variables(char *argv);

int	init_shvar(const char *name, const char *const content);

int	shellvar_assignement_parsing(const char *const str);

void	free_all_shvar(void);

/* Utils */
int		get_index(char *str);
_Bool	contains_array_subscript(char *str);

#endif
