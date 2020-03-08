/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_newstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:06:54 by efischer          #+#    #+#             */
/*   Updated: 2019/10/29 14:43:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"vctlib.h"

t_vector	*vct_newstr(const char *str)
{
	t_vector	*vct;

	vct = (t_vector*)malloc(sizeof(t_vector));
	if (vct != NULL)
	{
		vct->len = ft_strlen(str);
		vct->size = DFL_SIZE;
		vct->scale = DFL_SCALE;
		if (vct->len + 1 > vct->size)
			vct_resize(vct);
		else
			vct->str = (char*)malloc(sizeof(char) * vct->size);
		ft_bzero(vct->str, vct->size);
		if (vct->str != NULL)
			vct->str = (char*)ft_memmove(vct->str, str, vct->len);
	}
	return (vct);
}
