/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:06:45 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 16:26:28 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_list			*get_shell_var(char *name)
{
	t_list	*head;
	t_list	*elem;

	head = g_env;
	elem = NULL;
	while (g_env != NULL)
	{
		if (ft_strequ(name, ((t_shell_var*)(g_env->content))->name))
		{
			elem = g_env;
			break ;
		}
		g_env = g_env->next;
	}
	g_env = head;
	return (elem);
}
