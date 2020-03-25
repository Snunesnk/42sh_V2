/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:12:28 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 16:26:27 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int		add_var_to_env(char *name, char *value, t_list *elem)
{
	t_shell_var	shell_var;
	t_list		*lst_new;

	ft_bzero(&shell_var, sizeof(shell_var));
	if (elem != NULL)
	{
		if (value != NULL)
			((t_shell_var*)(elem->content))->value = value;
		((t_shell_var*)(elem->content))->flag |= (SET | EXPORT);
	}
	else
	{
		shell_var.name = name;
		if (value != NULL)
		{
			shell_var.value = value;
			shell_var.flag |= SET;
		}
		shell_var.flag |= EXPORT;
		lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
		if (lst_new == NULL)
			return (FAILURE);
		ft_lstadd(&g_env, lst_new);
	}
	return (SUCCESS);
}

int				add_var(char **av)
{
	t_list		*elem;
	char		*name;
	char		*value;
	size_t		i;

	i = 0;
	while (av[i] != NULL)
	{
		value = ft_strchr(av[i], '=');
		if (value != NULL)
		{
			name = ft_strndup(av[i], value - av[i]);
			value = ft_strdup(value + 1);
		}
		else
			name = ft_strdup(av[i]);
		elem = get_shell_var(name, g_env);
		if (add_var_to_env(name, value, elem) == FAILURE)
			return (FAILURE);
		i++;
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (SUCCESS);
}
