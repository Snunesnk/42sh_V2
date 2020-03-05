/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:43:11 by efischer          #+#    #+#             */
/*   Updated: 2020/03/05 08:43:28 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_set(t_list *env, t_list **elem)
{
	char	*tmp;

	tmp = NULL;
	if ((((t_shell_var*)(env->content))->flag & SET) == SET)
	{
		ft_asprintf(&tmp, "%s=\"%s\"\n", ((t_shell_var*)(env->content))->name,
				((t_shell_var*)(env->content))->value);
	}
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
}

int		cmd_set(int ac, char **av)
{
	extern t_list	*g_env;

	(void)ac;
	(void)av;
	if (ac == 1)
		ft_lstprint(g_env, &print_set);
	return (e_success);
}
