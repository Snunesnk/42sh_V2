/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 09:56:01 by efischer          #+#    #+#             */
/*   Updated: 2020/03/12 10:28:34 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_tab(int ac, char ***av)
{
	int		i;

	i = 0;
	if (*av == NULL)
		return ;
	while (i < ac)
	{
		free(*av[i]);
		*av[i] = NULL;
		i++;
	}
	free(*av);
	*av = NULL;
}
