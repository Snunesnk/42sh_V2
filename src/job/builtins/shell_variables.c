/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/11 18:16:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "shell_variables.h"

/* to test index overflow  9223372036854775810*/

struct s_shvar	*g_shellvar = NULL;

/*
void	print_shellvar(void)
{
	int	i;

	i = 0;
	if (g_shellvar)
	{
		while (g_shellvar[i])
		{
			ft_printf("%s=\n", g_shellvar[i].);
		}
	}
}*/

int	append_shvar(const char *name, const char *const content)
{
	extern struct s_shvar	*g_shellvar;

	if (!g_shellvar)
	{
		g_shellvar = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
		g_shellvar->value = (char*)name;
		g_shellvar->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
		g_shellvar->next_content->value = (char*)content;
		g_shellvar->index = 0;
		g_shellvar->next_var = NULL;
	}
	return (0);
}

int	ft_split_assignement(const char *const name)
{
	char *ptr;
	char *cpy;
	
	cpy = ft_strdup(name);
	ptr = ft_strstr(cpy, "=");
	*ptr = '\0';
	++ptr;
	append_shvar(cpy, ptr);
	return (0);
}