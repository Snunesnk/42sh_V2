/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:22:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/11 18:11:54 by abarthel         ###   ########.fr       */
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
};

extern struct s_shvar		*g_shellvar;

#endif
