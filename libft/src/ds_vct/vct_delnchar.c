/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_delnchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:12:26 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 14:12:27 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

void	vct_delnchar(t_vector *vct, size_t pos, size_t n)
{
	if (vct != NULL && pos <= vct->len)
	{
		ft_memmove(vct->str + pos, vct->str + pos + n, vct->len - pos - n);
		vct->len -= n;
	}
}
