/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_addchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:02:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/29 15:17:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

int		vct_addchar(const char c, t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
	{
		if (vct->len + 1 > vct->size)
			ret = vct_resize(vct);
		if (ret == SUCCESS)
			vct->str[vct->len] = c;
	}
	return (ret);
}
