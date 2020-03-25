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

t_list			*get_shell_var(char *name, t_list *svar_lst)
{
	while (svar_lst)
	{
		if (ft_strequ(name, ((t_shell_var*)(svar_lst->content))->name))
			break ;
		svar_lst = svar_lst->next;
	}
	return (svar_lst);
}
