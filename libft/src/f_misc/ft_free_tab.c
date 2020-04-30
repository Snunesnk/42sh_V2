/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 09:56:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/12 10:28:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_tab(int ac, char ***av)
{
	int		i;

	i = 0;
	if (*av == NULL)
		return ;
	while (i < ac && (*av)[i] != NULL)
	{
		free((*av)[i]);
		(*av)[i] = NULL;
		i++;
	}
	free(*av);
	*av = NULL;
}
