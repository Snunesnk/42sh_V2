/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_addstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:22:34 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/29 14:22:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vctlib.h"

int		vct_addstr(const char *str, t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
	{
		vct->len += ft_strlen(str);
		if (vct->len + 1 > vct->size)
			ret = vct_resize(vct);
		if (ret == SUCCESS)
			vct->str = ft_strcat(vct->str, str);
	}
	return (ret);
}
