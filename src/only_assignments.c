/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:52:47 by efischer          #+#    #+#             */
/*   Updated: 2020/03/05 13:18:05 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		only_assignments(t_process *p)
{
	extern t_list	*g_env;
	t_shell_var		shell_var;
	t_list			*lst_new;
	t_list			*tmp_lst;
	t_list			*elem;
	char			*name;
	char			*value;
	int				ret;
	int				i;

	i = 0;
	ret = FALSE;
	tmp_lst = NULL;
	ft_bzero(&shell_var, sizeof(shell_var));
	while (i < p->argc)
	{
		value = ft_strchr(p->argv[i], '=');
		if (value != NULL)
		{
			name = ft_strndup(p->argv[i], value - p->argv[i]);
			value = ft_strdup(value + 1);
			elem = get_shell_var(name);
			if (elem != NULL)
			{
				if (value != NULL)
					((t_shell_var*)(elem->content))->value = value;
				((t_shell_var*)(elem->content))->flag |= SET;
				((t_shell_var*)(elem->content))->flag |= EXPORT;
			}
			else
			{
				shell_var.name = name;
				shell_var.value = value;
				shell_var.flag |= SET;
				shell_var.flag |= EXPORT;
				lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
				if (lst_new == NULL)
				{
					ft_lstdel(&tmp_lst, &del_env);
					return (FAILURE);
				}
				ft_lstadd(&tmp_lst, lst_new);
			}
		}
		else
			break ;
		i++;
	}
	if (i == p->argc)
	{
		ft_lstadd(&g_env, tmp_lst);
		ft_merge_sort(&g_env, &alpha_sort);
		ret = TRUE;
	}
	else
		ft_lstdel(&tmp_lst, &del_env);
	return (ret);
}
