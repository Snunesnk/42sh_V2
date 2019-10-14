/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/14 15:50:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "shell_variables.h"
#include "error.h"

/* to test index overflow  9223372036854775810*/

struct s_shvar	*g_shellvar = NULL;

int	init_shvar(const char *name, const char *const content)
{
	extern struct s_shvar	*g_shellvar;
	
	g_shellvar = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!g_shellvar)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->value = (char*)name;
	g_shellvar->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!g_shellvar->next_content)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->next_content->value = (char*)content;
	g_shellvar->index = 0;
	g_shellvar->next_var = NULL;
	return (e_success);
}

int	append_shvar(const char *const name, const char *const content)
{
	extern struct s_shvar	*g_shellvar;
	struct s_shvar		*tmp;

	tmp = g_shellvar;
	while (tmp->next_var)
	{
		tmp = tmp->next_var;
	}
	tmp->next_var = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp)
		return (e_cannot_allocate_memory);
	tmp = tmp->next_var;
	tmp->value = (char*)name;
	tmp->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp->next_content)
		return (e_cannot_allocate_memory);
	tmp->next_content->value = (char*)content;
	tmp->index = 0;
	tmp->next_var = NULL;
	return (e_success);
}

int	ft_split_assignement(const char *const name)
{
	extern struct s_shvar	*g_shellvar;
	char *ptr;
	char *cpy;
	
	cpy = ft_strdup(name);
	if (!cpy)
		return (e_cannot_allocate_memory);
	ptr = ft_strstr(cpy, "=");
	*ptr = '\0';
	++ptr;
	if (!g_shellvar)
		init_shvar(cpy, ptr);
	else
		append_shvar(cpy, ptr);
	return (e_success);
}
