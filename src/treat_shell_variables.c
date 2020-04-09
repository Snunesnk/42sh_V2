/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:33:10 by efischer          #+#    #+#             */
/*   Updated: 2020/03/12 10:29:08 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include  "shell.h"

char	**tab_remove_first_elem(int *ac, char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	(*ac)--;
	new_tab = (char**)malloc(sizeof(char*) * *ac);
	if (new_tab == NULL)
		return (NULL);						
	if (*ac > 0)
	{
		while (i < *ac)
		{
			new_tab[i] = ft_strdup(av[i + 1]);
			i++;
		}
		ft_free_tab((*ac) + 1, &av);
	}
	else
		new_tab = NULL;
	return (new_tab);
}

int		treat_shell_variables(t_process *p, int	opt)
{
	extern t_list	*g_env;
	t_shell_var		shell_var;
	t_list			*lst_new;
	t_list			*elem;
	char			*name;
	char			*value;

	ft_bzero(&shell_var, sizeof(shell_var));
	while (p->argv != NULL && (value = ft_strchr(p->argv[0], '=')) != NULL)
	{
		if (value != NULL && opt == 1)
		{
			name = ft_strndup(p->argv[0], value - p->argv[0]);
			value = ft_strdup(value + 1);
			elem = get_shell_var(name, g_env);
			if (elem != NULL)
			{
				((t_shell_var*)(elem->content))->value = value;
				((t_shell_var*)(elem->content))->flag |= SET;
			}
			else
			{
				shell_var.name = name;
				shell_var.value = value;
				shell_var.flag |= SET;
				lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
				if (lst_new == NULL)
					return (FAILURE);
				ft_lstadd(&g_env, lst_new);
			}
		}
		if ((p->argv = tab_remove_first_elem(&p->argc, p->argv)) == NULL)
			break ;
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (SUCCESS);
}
