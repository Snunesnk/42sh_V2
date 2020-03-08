/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:07:48 by efischer          #+#    #+#             */
/*   Updated: 2019/10/29 12:57:54 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"vctlib.h"

t_vector	*vct_new(void)
{
	t_vector	*vct;

	vct = (t_vector*)malloc(sizeof(t_vector));
	if (vct != NULL)
	{
		vct->len = 0;
		vct->size = DFL_SIZE;
		vct->scale = DFL_SCALE;
		vct->str = (char*)malloc(sizeof(char) * vct->size);
		if (vct->str != NULL)
			ft_bzero(vct->str, vct->size);
	}
	return (vct);
}
