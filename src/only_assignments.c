/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:52:47 by efischer          #+#    #+#             */
/*   Updated: 2020/04/10 14:01:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		only_assignments(t_process *p)
{
	int i;

	i = 0;
	if (p->argc)
	{
		while (i < p->argc)
		{
			if (ft_strchr(p->argv[i], '=') == NULL)
				break ;
			i++;
		}
		if (i == p->argc)
			return (1);
	}
	return (0);
}
