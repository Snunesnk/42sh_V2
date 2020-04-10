/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_char_classes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:42:34 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 12:44:31 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_CHAR_CLASSES_H
# define G_CHAR_CLASSES_H

# include <stddef.h>

/*
** length of the longest char_class name, so that
** it can be stored in a static char array
*/

# define MAX_CHAR_CLASS_NAME	8

typedef int					(*t_char_class_fct)(char);

typedef struct				s_char_class
{
	const char			*name;
	t_char_class_fct	f;
}							t_char_class;

extern const t_char_class	g_char_classes[];

int							ft_fnm_is_alnum(char c);
int							ft_fnm_is_digit(char c);
int							ft_fnm_is_punct(char c);
int							ft_fnm_is_alpha(char c);
int							ft_fnm_is_graph(char c);
int							ft_fnm_is_space(char c);
int							ft_fnm_is_blank(char c);
int							ft_fnm_is_lower(char c);
int							ft_fnm_is_upper(char c);
int							ft_fnm_is_cntrl(char c);
int							ft_fnm_is_print(char c);
int							ft_fnm_is_xdigit(char c);

t_char_class_fct			get_char_class_fct(const char *name, size_t len);

#endif
