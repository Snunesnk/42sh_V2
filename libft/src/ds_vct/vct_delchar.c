/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_delchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:33:09 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:33:12 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

void	vct_delchar(t_vector *vct, size_t pos)
{
	if (vct != NULL && pos <= vct->len)
	{
		ft_memmove(vct->str + pos, vct->str + pos + 1, vct->len - pos);
		vct->len--;
	}
}
