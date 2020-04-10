/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:26:38 by efischer          #+#    #+#             */
/*   Updated: 2020/04/10 14:12:48 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

int		vct_reset(t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
	{
		ft_strdel(&vct->str);
		vct->len = 0;
		vct->size = DFL_SIZE;
		vct->scale = DFL_SCALE;
		vct->str = (char*)malloc(sizeof(char) * vct->size);
		ft_bzero(vct->str, vct->size);
		if (vct->str == NULL)
			ret = FAILURE;
	}
	return (ret);
}
