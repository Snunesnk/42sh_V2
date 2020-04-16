/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 13:55:13 by abarthel         ###   ########.fr       */
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
