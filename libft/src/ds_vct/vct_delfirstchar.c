/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_delfirstchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:12:34 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 14:12:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

void	vct_delfirstchar(t_vector *vct)
{
	if (vct != NULL)
	{
		ft_memmove(vct->str, vct->str + 1, vct->len);
		vct->len--;
	}
}
