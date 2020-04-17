/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/17 13:36:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int				add_var(char **av)
{
	char		*name;
	char		*value;
	size_t		i;

	i = 0;
	while (av[i] != NULL)
	{
		if (get_assignment(av[i], &name, &value) == SUCCESS)
			*value++ = 0;
		else if (!*name || *name == '=')
			return (FAILURE);
		if (set_shell_var(name, value,
			EXPORT | (value ? SET : 0), &g_env) == FAILURE)
			return (FAILURE);
		++i;
	}
	ft_merge_sort(&g_env, alpha_sort);
	return (SUCCESS);
}
